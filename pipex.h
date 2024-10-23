/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <tlukan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:48:17 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/23 16:20:11 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

void	baby_fork(char **argv, int *fd, char **envp);
void	daddy_fork(char **argv, int *fd, char **envp);
void	exe_func(char *argv, char **envp);
char	*find_path(char *fun, char **envp);
char	*get_line_path(char **envp);
void	check_args(int argc);
void	create_pipe(int *fd);
pid_t	create_child(int is_first, char **argv, int *fd, char **envp);
void	wait_for_children(pid_t pidone, pid_t pidtwo);
void	child_process(char **argv, int *fd, char **envp, int is_first);
char	*get_path_from_env(char **envp);
void	childsplit(char **argv, int is_first, int *fd, int file);

#endif