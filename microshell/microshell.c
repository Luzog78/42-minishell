/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:05:26 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 14:21:30 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int err(char *s) {
	while (*s)
		write(2, s++, 1);
	return 1;
}

int cd(int i, char **av) {
	if (i != 2)
		return err("error: bad argument\n");
	if (chdir(av[1]) == -1)
		return err("error: cannot change path to ") & err(av[1]) & err("\n");
	return 0;
}

int ex(int i, char **av, char **env) {
	int status;
	int fd[2];
	int is_pipe = av[i] && !strcmp(av[i], "|");

	if (is_pipe && pipe(fd) == -1)
		return err("error: fatal\n");
	
	int pid = fork();
	if (!pid) {
		av[i] = 0;
		if (is_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err("error: fatal\n");
		execve(av[0], av, env);
		return err("error: cannot execute ") & err(av[0]) & err("\n");;
	} else {
		waitpid(pid, &status, 0);
		if (is_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err("error: fatal\n");
		return WIFEXITED(status) && WEXITSTATUS(status);
	}
}

int main(int ac, char **av, char **env) {
	int status = 0;
	int i = 0;

	if (ac > 1)
		while (av[i] && av[++i]) {
			av += i;
			i = 0;
			while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
				i++;
			if (!strcmp(av[0], "cd"))
				status = cd(i, av);
			else if (i)
				status = ex(i, av, env);
		}
	return status;
}
