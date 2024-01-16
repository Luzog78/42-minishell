/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 03:07:38 by bcarolle          #+#    #+#             */
/*   Updated: 2024/01/16 00:57:54 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_subshell	*ft_subshell_add(t_subshell **subshell, t_cmd_type type, char **env)
{
	t_subshell	*new_subshell;
	t_subshell	*tmp;

	new_subshell = calloc(1, sizeof(t_subshell));
	if (!new_subshell)
		return (NULL);
	ft_subshell_init(new_subshell, type, env);
	if (!*subshell)
	{
		*subshell = new_subshell;
		return (new_subshell);
	}
	tmp = *subshell;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_subshell;
	return (new_subshell);
}

t_bool	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\0');
}

void	ft_skip_whitespace(char **str)
{
	while (**str && ft_is_whitespace(**str))
		(*str)++;
}

t_bool	ft_starts_with(char *str, char *prefix)
{
	int	i;

	i = 0;
	while (str[i] && prefix[i])
	{
		if (str[i] != prefix[i])
			return (FALSE);
		i++;
	}
	if (prefix[i])
		return (FALSE);
	return (TRUE);
}

char	*ft_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	substr = calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

char	*ft_get_next_word(char **str)
{
	char	*tmp;
	char	*word;
	char	quote;

	ft_skip_whitespace(str);
	tmp = *str;
	while (*tmp && (!ft_is_whitespace(*tmp) || quote))
	{
		if (*tmp == '\'' || *tmp == '"')
		{
			if (!quote)
				quote = *tmp;
			else if (quote == *tmp)
				quote = 0;
		}
		tmp++;
	}
	word = ft_substr(*str, 0, tmp - *str);
	*str = tmp;
	return (word);
}

int	ft_get_next_int(char **str)
{
	int		nb;
	char	*tmp;

	ft_skip_whitespace(str);
	tmp = *str;
	nb = 0;
	while (*tmp && *tmp >= '0' && *tmp <= '9')
	{
		nb = nb * 10 + *tmp - '0';
		tmp++;
	}
	*str = tmp;
	return (nb);
}

t_out_type	ft_get_out_redirection(char *str)
{
	int	i;

	i = 0;
	ft_skip_whitespace(&str);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	if (str[i] != '>')
		return (NO_OUT);
	if (str[i + 1] != '>')
		return (REPLACE);
	return (APPEND);
}

t_out	*ft_out_add(t_out **out, int from, char *to, t_out_type type)
{
	t_out	*new_out;
	t_out	*tmp;

	new_out = calloc(1, sizeof(t_out));
	if (!new_out)
		return (NULL);
	new_out->from = from;
	new_out->to = to;
	new_out->type = type;
	if (!*out)
	{
		*out = new_out;
		return (new_out);
	}
	tmp = *out;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_out;
	return (new_out);
}

t_argv	*ft_argv_add(t_argv **argv, char *arg)
{
	t_argv	*new_argv;
	t_argv	*tmp;

	new_argv = calloc(1, sizeof(t_argv));
	if (!new_argv)
		return (NULL);
	new_argv->arg = arg;
	new_argv->next = NULL;
	if (!*argv)
	{
		*argv = new_argv;
		return (new_argv);
	}
	tmp = *argv;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_argv;
	return (new_argv);
}

void	ft_parse_redirection(t_subshell *subshell, char **str)
{
	int		fd;
	t_out	*ret;

	ft_skip_whitespace(str);
	fd = 1;
	if (**str >= '0' && **str <= '9')
		fd = ft_get_next_int(str);
	(*str)++;
	if (**str != '>')
		ret = ft_out_add(&subshell->outfiles, fd, ft_get_next_word(str), REPLACE);
	else
	{
		(*str)++;
		ret = ft_out_add(&subshell->outfiles, fd, ft_get_next_word(str), APPEND);
	}
	if (!ret)
		subshell->exit_status = 1;
}

void	ft_parse_cmd(t_subshell *subshell, char **str)
{
	char	*cursor;
	char	*tmp;
	int		parsing_state; // 0: start, 1: argv, 2: redirections

	parsing_state = 0;
	cursor = *str;
	while (*cursor)
	{
		ft_skip_whitespace(&cursor);
		if (ft_starts_with(cursor, "<"))
		{
			cursor++;
			tmp = ft_get_next_word(&cursor);
			subshell->infile = tmp;
		}
		else if (ft_get_out_redirection(cursor) != NO_OUT)
		{
			ft_parse_redirection(subshell, &cursor);
			if (parsing_state == 1)
				parsing_state = 2;
		}
		else if (ft_starts_with(cursor, "<<"))
		{
			cursor += 2;
			tmp = ft_get_next_word(&cursor);
			if (!*tmp)
				subshell->exit_status = 1;
			subshell->heredoc_limiter = tmp;
			if (parsing_state == 1)
				parsing_state = 2;
		}
		else if (ft_starts_with(cursor, "&&"))
		{
			subshell->link = AND;
			cursor += 2;
			break ;
		}
		else if (ft_starts_with(cursor, "||"))
		{
			subshell->link = OR;
			cursor += 2;
			break ;
		}
		else if (ft_starts_with(cursor, "|&"))
		{
			subshell->link = PIPE_AND;
			cursor += 2;
			break ;
		}
		else if (ft_starts_with(cursor, "|"))
		{
			subshell->link = PIPE;
			cursor++;
			break ;
		}
		else
		{
			if (parsing_state == 0)
				parsing_state = 1;
			if (parsing_state == 2)
				subshell->exit_status = 1;
			tmp = ft_get_next_word(&cursor);
			ft_argv_add(&subshell->argv, tmp);
		}
	}
	*str = cursor;
}

t_bool	ft_check_parenthesis_and_quotes(char *str)
{
	int		i;
	char	quote;
	int		parenthesis;

	i = 0;
	quote = 0;
	parenthesis = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		else if (str[i] == '(' && !quote)
			parenthesis++;
		else if (str[i] == ')' && !quote)
			parenthesis--;
		if (parenthesis < 0)
			return (FALSE);
		i++;
	}
	if (quote || parenthesis)
		return (FALSE);
	return (TRUE);
}

void	ft_parse(t_subshell *subshell, char *str)
{
	t_subshell	*curr_cmd;
	char		*cursor;

	curr_cmd = subshell->cmds;
	cursor = str;
	if (!*cursor || ft_is_empty(cursor))
		subshell->exit_status = 1;
	while (*cursor && !ft_is_empty(cursor))
	{
		ft_skip_whitespace(&cursor);
		if (*cursor == '(')
		{
			curr_cmd = ft_subshell_add(&subshell->cmds, SUBSHELL, subshell->env);
			ft_parse(curr_cmd, cursor + 1);
			while (*cursor && *cursor != ')')
				cursor++;
			if (*cursor != ')')
				subshell->exit_status = 1;
			cursor++;
		}
		else if (*cursor == ')')
		{
			break ;
		}
		else
		{
			curr_cmd = ft_subshell_add(&subshell->cmds, COMMAND, subshell->env);
			ft_parse_cmd(curr_cmd, &cursor);
		}
	}
	free(str);
}
