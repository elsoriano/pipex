/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:28:49 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/08 17:54:33 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fd[2];
	int	pid;
	int	n;
	int	buff;

	if (!argv[0] || !argv)
		return (1);
	if (argc == 0)
		return (2);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	if (pipe(fd) == -1)
		return (3);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid > 0)
	{
		printf("this is the parent process. PID = %d\n", pid);
		close(fd[1]);
		read(fd[0], &buff, sizeof(int));
		printf("result of buff = %d\n", buff);
		wait(NULL);
	}
	else
	{
		n = 20;
		printf("this is the child process. PID = %d\n", pid);
		close(fd[0]);
		write(fd[1], &n, sizeof(int));
	}
}
