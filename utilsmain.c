/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <tlukan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:39:24 by tlukan            #+#    #+#             */
/*   Updated: 2024/10/23 16:00:27 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc)
{
	if (argc != 5)
	{
		perror("Controllo argomenti");
		exit(EXIT_FAILURE);
	}
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t	create_child(int is_first, char **argv, int *fd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Fork fallita");
	else if (pid == 0)
	{
		child_process(argv, fd, envp, is_first);
		exit(0);
	}
	return (pid);
}

void	wait_for_children(pid_t pidone, pid_t pidtwo)
{
	waitpid(pidone, NULL, 0);
	waitpid(pidtwo, NULL, 0);
}

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp (envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
