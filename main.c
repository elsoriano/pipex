/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:28:49 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/11 14:31:32 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../inc/libft/inc/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipend[2];
	int		pid;
	int		fd;
	int		fdout;
	int		pipend2[2];
	char 	**arr1;
	char 	**arr2;

	arr1 = ft_split(argv[2], ' ');
	arr2 = ft_split(argv[3], ' ');
	if (!argv[0] || !argv)
		return (1);
	if (argc == 0)
		return (2);
	fd = open(argv[1], O_RDONLY);
	fdout = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (4);
	if (pipe(pipend) == -1)
		return (3);
	if (pipe(pipend2) == -1)
		return (4);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid > 0)
	{
		//parent process
		printf("this is the parent process");
		dup2(pipend[0], STDIN_FILENO);
		close(pipend[0]);
		close(pipend[1]);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		execve("/bin/wc", arr2, envp);
		waitpid(pid, NULL, 0);
	}
	else
	{
		//child proccess
		printf("this is the child process");
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipend[1], STDOUT_FILENO);
		close(pipend[1]);
		close(pipend[0]);
		execve("/bin/wc", arr1, envp);
		perror("execve failed");
	}
	close (fd);
	close (fdout);
}
