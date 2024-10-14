/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:32:18 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/14 20:40:18 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft/inc/libft.h"
#include "../inc/pipex.h"

int	ft_error_exit(t_index *i, char *msg)
{
	if (i && i->fd[0])
		close (i->fd[0]);
	if (i && i->fd[1])
		close (i->fd[1]);
	printf("%s\n", msg);
	exit (EXIT_FAILURE);
}

char	*ft_found_path(char *paths, char *cmd)
{
	char	**paths_split;
	char	*cmd_path;
	int		i;

	paths_split = ft_split(paths, ':');
	if (!paths_split)
		return (NULL);
	i = 0;
	while (paths_split[i])
	{
		cmd_path = ft_strjoin(paths_split[i], ft_strjoin("/", cmd));
		free(paths_split[i]);
		if (access(cmd_path, R_OK | X_OK | F_OK) == 0)
		{
			while (paths_split[i + 1])
				free(paths_split[i++ + 1]);
			free(paths_split);
			return (cmd_path);
		}
		i++;
	}
	free(paths_split);
	return (NULL);
}

char	*ft_paths(t_index *i, char *cmd, char **envp)
{
	int		k;
	char	*path;

	k = 0;
	path = NULL;
	while (envp[k])
	{
		if (ft_strnstr(envp[k], "PATH=", 5))
		{
			path = ft_found_path(envp[k] + 5, cmd);
			if (!path)
				ft_error_exit(i, "Command not Found");
			return (path);
		}
		k++;
	}
	ft_error_exit(i, "No path in environment");
	return (NULL);
}

void	ft_exec(t_index *i, char **envp)
{
	i->pid = fork();
	if (i->pid == -1)
		ft_error_exit(i, "Error creating subprocess");
	if (i->pid > 0)
	{
		dup2(i->pipe1[0], STDIN_FILENO);
		dup2(i->fd[1], STDOUT_FILENO);
		close(i->fd[1]);
		close(i->pipe1[1]);
		execve (i->path2, i->cmd2, envp);
		ft_error_exit(i, "Could not execute command 2");
		waitpid(i->pid, NULL, 0);
	}
	else
	{
		dup2(i->fd[0], STDIN_FILENO);
		close(i->fd[0]);
		dup2(i->pipe1[1], STDOUT_FILENO);
		close(i->pipe1[0]);
		execve (i->path1, i->cmd1, envp);
		ft_error_exit(i, "Could not execute command 1");
	}
}

void	ft_open_files(t_index *i, char *infile, char *outfile)
{
	i->fd[0] = open(infile, O_RDONLY);
	if (i->fd[0] == -1)
	{
		perror("A problem ocurred when opening infile");
		exit(EXIT_FAILURE);
	}
	i->fd[1] = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (i->fd[1] == -1)
	{
		close (i->fd[0]);
		perror("A problem ocurred setting outfile");
		exit(EXIT_FAILURE);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_index	i;

	if (argc != 5)
		return (ft_error_exit(NULL, "Invalid number of arguments"));
	ft_open_files(&i, argv[1], argv[argc - 1]);
	i.cmd1 = ft_split(argv[2], ' ');
	i.cmd2 = ft_split(argv[3], ' ');
	i.path1 = ft_paths(&i, i.cmd1[0], envp);
	i.path2 = ft_paths(&i, i.cmd2[0], envp);
	pipe(i.pipe1);
	if (!i.pipe1)
		return (ft_error_exit(&i, "Error creating pipe"));
	ft_exec(&i, envp);
	free (i.cmd1);
	free (i.cmd2);
	free (i.path1);
	free (i.path2);
	close (i.fd[0]);
	close (i.fd[1]);
}
