/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <tlukan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:45:52 by fluzi             #+#    #+#             */
/*   Updated: 2024/10/23 17:17:24 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_executable_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*full_path;
	char	*final_path;

	paths = ft_split(get_path_from_env(envp), ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(final_path, X_OK) == 0)
		{
			ft_free_array(paths);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free_array(paths);
	perror("Comando non trovato");
	return (NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = find_executable_path(args[0], envp);
	if (!path)
		exit(EXIT_FAILURE);
	execve(path, args, envp);
	perror("Esecuzione fallita");
	ft_free_array(args);
	free(path);
}

void	child_process(char **argv, int *fd, char **envp, int is_first)
{
	int		file;
	char	*command;

	file = 0;
	childsplit(argv, is_first, fd, file);
	if (is_first)
		command = argv[2];
	else
		command = argv[3];
	execute_command(command, envp);
	if (file != -1)
		close(file);
	else
		perror("Errore nell'apertura del file");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pidone;
	pid_t	pidtwo;
	int		fd[2];

	check_args(argc);
	create_pipe(fd);
	pidone = create_child(1, argv, fd, envp);
	pidtwo = create_child(0, argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	wait_for_children(pidone, pidtwo);
	return (0);
}
