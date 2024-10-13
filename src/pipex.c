/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:32:18 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/13 11:35:08 by rhernand         ###   ########.fr       */
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

void	ft_exec(t_index *i, char **argv, char **envp)
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
		execve ("/bin/wc", ft_split(argv[3], ' '), envp);
		ft_error_exit(i, "Could not execute command 2");
		waitpid(i->pid, NULL, 0);
	}
	else
	{
		dup2(i->fd[0], STDIN_FILENO);
		close(i->fd[0]);
		dup2(i->pipe1[1], STDOUT_FILENO);
		close(i->pipe1[0]);
		execve ("/bin/wc", ft_split(argv[2], ' '), envp);
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

	if (argc < 5)
		return (ft_error_exit(NULL, "Invalid number of arguments"));
	ft_open_files(&i, argv[1], argv[argc - 1]);
	pipe(i.pipe1);
	if (!i.pipe1)
		return (ft_error_exit(&i, "Error creating pipe"));
	ft_exec(&i, argv, envp);
}
