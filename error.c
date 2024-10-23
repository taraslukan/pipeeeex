/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <tlukan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:04:55 by tlukan            #+#    #+#             */
/*   Updated: 2024/10/23 17:15:17 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error(void)
{
	perror("error\n");
	return (1);
}

void	childsplit(char **argv, int is_first, int *fd, int file)
{
	if (is_first)
	{
		if (access(argv[1], R_OK) < 0)
			exit(error());
		file = open(argv[1], O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
}
