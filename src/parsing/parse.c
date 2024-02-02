/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 03:07:38 by bcarolle          #+#    #+#             */
/*   Updated: 2024/02/02 17:23:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_subshell(t_subshell *subshell)
{
	t_subshell	*tmp;
	t_str_lst	*tmp2;
	t_out		*tmp3;
	t_stdin_lst	*tmp4;
	t_subshell	*tmp5;

	tmp = subshell;
	while (tmp)
	{
		while (tmp->argv)
		{
			tmp2 = tmp->argv;
			tmp->argv = tmp->argv->next;
			free(tmp2->value);
			free(tmp2);
		}
		while (tmp->outfiles)
		{
			tmp3 = tmp->outfiles;
			tmp->outfiles = tmp->outfiles->next;
			free(tmp3->to);
			free(tmp3);
		}
		while (tmp->stdin)
		{
			tmp4 = tmp->stdin;
			tmp->stdin = tmp->stdin->next;
			free(tmp4->value);
			free(tmp4);
		}
		ft_free_subshell(tmp->cmds);
		ft_free_char_array(tmp->env);
		tmp->cmds = NULL;
		tmp->argv = NULL;
		tmp->outfiles = NULL;
		tmp->stdin = NULL;
		tmp5 = tmp;
		tmp = tmp->next;
		free(tmp5);
	}
}

/* *********************************************** */
/* **********************echo > a << b || g && (e | < 98 f)************************* */
/* *********************************************** */

int	ft_error(int err, char *str, t_subshell *subshell_to_free)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	// ft_free_subshell(subshell_to_free);
	(void)subshell_to_free;
	return (err);
}

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

t_bool ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\0');
}

t_bool	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
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

t_str_lst	*ft_str_lst_add(t_str_lst **lst, char *str)
{
	t_str_lst	*new_argv;
	t_str_lst	*tmp;

	new_argv = calloc(1, sizeof(t_str_lst));
	if (!new_argv)
		return (NULL);
	new_argv->value = str;
	new_argv->next = NULL;
	if (!*lst)
	{
		*lst = new_argv;
		return (new_argv);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_argv;
	return (new_argv);
}

char	*ft_concat_lst(t_str_lst *lst)
{
	char		*str;
	t_str_lst	*tmp;
	int			len;

	len = 0;
	tmp = lst;
	while (lst)
	{
		len += ft_strlen(lst->value);
		lst = lst->next;
	}
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	lst = tmp;
	while (lst)
	{
		ft_strcat(str, lst->value);
		lst = lst->next;
	}
	return (str);
}

void	ft_free_str_list(t_str_lst *lst)
{
	t_str_lst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

t_bool	ft_is_next_a_fd(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '>')
		return (TRUE);
	return (FALSE);
}

char	*ft_get_next_word(char **str)
{
	t_str_lst	*lst;
	char		quote;
	char		*word;
	int			i;
	int			start_idx;

	ft_skip_whitespace(str);
	quote = 0;
	lst = NULL;
	i = 0;
	start_idx = 0;
	while ((*str)[i] && (!ft_is_whitespace((*str)[i]) || quote))
	{
		if (((*str)[i] == '\'' || (*str)[i] == '"') && !quote)
		{
			if (i - start_idx > 0)
				ft_str_lst_add(&lst, ft_substr(*str, start_idx, i - start_idx));
			quote = (*str)[i];
			start_idx = i + 1;
		}
		else if (((*str)[i] == '\'' || (*str)[i] == '"') && quote == (*str)[i])
		{
			quote = 0;
			ft_str_lst_add(&lst, ft_substr(*str, start_idx, i - start_idx));
			start_idx = i + 1;
		}
		else if (!quote && ((*str)[i] == '<' || (*str)[i] == '>'
			|| (*str)[i] == '|' || (*str)[i] == ';'
			|| (*str)[i] == '(' || (*str)[i] == ')' || ft_is_next_a_fd((*str) + i)))
			break ;
		i++;
	}
	if (i - start_idx > 0)
		ft_str_lst_add(&lst, ft_substr(*str, start_idx, i - start_idx));
	word = ft_concat_lst(lst);
	ft_free_str_list(lst);
	(*str) += i;
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

	if (!to)
		return (NULL);
	if (!*to)
	{
		free(to);
		return (NULL);
	}
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

t_stdin_lst	*ft_stdin_add(t_stdin_lst **stdin, char *value, t_stdin_type type)
{
	t_stdin_lst	*new_stdin;
	t_stdin_lst	*tmp;

	new_stdin = calloc(1, sizeof(t_stdin_lst));
	if (!new_stdin)
		return (NULL);
	new_stdin->value = value;
	new_stdin->type = type;
	if (!*stdin)
	{
		*stdin = new_stdin;
		return (new_stdin);
	}
	tmp = *stdin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_stdin;
	return (new_stdin);
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
		subshell->exit_status = ft_error(2,
			"syntax error: missing redirection statement", NULL);
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

void	ft_skip_parenthesis(char **cursor)
{
	char	quote;
	int		parenthesis;

	quote = 0;
	parenthesis = 1;
	while (**cursor)
	{
		if (**cursor == '\'' || **cursor == '"')
		{
			if (!quote)
				quote = **cursor;
			else if (quote == **cursor)
				quote = 0;
		}
		else if (**cursor == '(' && !quote)
			parenthesis++;
		else if (**cursor == ')' && !quote)
			parenthesis--;
		if (parenthesis <= 0)
			break ;
		(*cursor)++;
	}
	(*cursor)++;
	ft_skip_whitespace(cursor);
	if (ft_starts_with(*cursor, "&&")
		|| ft_starts_with(*cursor, "||")
		|| ft_starts_with(*cursor, "|&"))
		*cursor += 2;
	else if (ft_starts_with(*cursor, "|"))
		(*cursor)++;
}

t_bool	ft_parse_subshell(t_subshell *subshell, char **str)
{
	t_subshell	*curr_cmd;
	char		*cursor;
	t_bool		ret;

	char	*tmp;
	int		parsing_state; // 0: start, 1: argv, 2: redirections

	curr_cmd = subshell->cmds;
	cursor = *str;

	ret = FALSE;
	parsing_state = 0;

	if (!*cursor || ft_is_empty(cursor))
		subshell->exit_status = ft_error(2,
			"syntax error: missing command", NULL);

	while (*cursor && !ft_is_empty(cursor))
	{
		ft_skip_whitespace(&cursor);
		if (ft_starts_with(cursor, "("))
		{
			if (parsing_state == 1 || subshell->type != UNDEFINED)
			{
				subshell->exit_status = ft_error(2,
					"syntax error: unexpected parenthesis '('", NULL);
				break ;
			}
			subshell->type = SUBSHELL;
			cursor++;
			while (!ret && *cursor && !ft_is_empty(cursor))
			{
				curr_cmd = ft_subshell_add(&subshell->cmds, UNDEFINED, subshell->env);
				ret = ft_parse_subshell(curr_cmd, &cursor);
				if (curr_cmd->exit_status)
				{
					subshell->exit_status = curr_cmd->exit_status;
					break ;
				}
			}
			parsing_state = 2;
			ret = FALSE;
		}
		else if (ft_starts_with(cursor, ")"))
		{
			cursor++;
			if (subshell->type == UNDEFINED)
			{
				subshell->exit_status = ft_error(2,
					"syntax error: unexpected parenthesis ')'", NULL);
				break ;
			}
			ret = TRUE;
			break ;
		}
		else if (ft_starts_with(cursor, "<<"))
		{
			cursor += 2;
			tmp = ft_get_next_word(&cursor);
			if (!*tmp)
				subshell->exit_status = ft_error(2,
					"syntax error: missing heredoc delimiter", NULL);
			ft_stdin_add(&subshell->stdin, tmp, HEREDOC);
			if (parsing_state == 1)
				parsing_state = 2;
		}
		else if (ft_starts_with(cursor, "<"))
		{
			cursor++;
			tmp = ft_get_next_word(&cursor);
			if (!*tmp)
				subshell->exit_status = ft_error(2,
					"syntax error: missing input file", NULL);
			ft_stdin_add(&subshell->stdin, tmp, INFILE);
			if (parsing_state == 1)
				parsing_state = 2;
		}
		else if (ft_get_out_redirection(cursor) != NO_OUT)
		{
			ft_parse_redirection(subshell, &cursor);
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
			if (subshell->type == SUBSHELL)
			{
				subshell->exit_status = ft_error(2,
					"syntax error: subshell and command not separated", NULL);
				break ;
			}
			subshell->type = COMMAND;
			if (parsing_state == 0)
				parsing_state = 1;
			if (parsing_state == 2)
				subshell->exit_status = ft_error(2,
					"syntax error: missing a separator", NULL);
			tmp = ft_get_next_word(&cursor);
			ft_str_lst_add(&subshell->argv, tmp);
		}
	}
	*str = cursor;
	if (subshell->type == UNDEFINED)
		subshell->exit_status = ft_error(2,
			"syntax error: missing command", NULL);
	return (ret);
}

void	ft_parse(t_subshell *subshell, char *str)
{
	t_bool		ret;
	char		*cursor;
	t_subshell	*curr_cmd;

	subshell->exit_status = 0;
	ret = FALSE;
	cursor = str;
	while (!ret && *cursor && !ft_is_empty(cursor))
	{
		curr_cmd = ft_subshell_add(&subshell->cmds, UNDEFINED, subshell->env);
		ret = ft_parse_subshell(curr_cmd, &cursor);
		if (curr_cmd->exit_status)
		{
			subshell->exit_status = curr_cmd->exit_status;
			break ;
		}
	}
	curr_cmd = subshell->cmds;
	while (curr_cmd && curr_cmd->next)
		curr_cmd = curr_cmd->next;
	if (curr_cmd && curr_cmd->link != NONE)
		subshell->exit_status = ft_error(2,
			"syntax error: missing command", NULL);
}
