/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:53 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/15 10:45:04 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_clear_exit(t_index *i, char *msg)
{
	int	j;

	j = 0;
	if (i && i->fd[0])
		close (i->fd[0]);
	if (i && i->fd[1])
		close (i->fd[1]);
	if (i && i->cmd1[0])
		while (i->cmd1[j])
			free(i->cmd1[j++]);
	if (i && i->cmd1)
		free(i->cmd1);
	j = 0;
	if (i && i->cmd2[0])
		while (i->cmd2[j])
			free(i->cmd2[j++]);
	if (i && i->cmd2)
		free(i->cmd2);
	if (i && i->path1)
		free(i->path1);
	if (i && i->path2)
		free(i->path2);
	if (!msg)
		exit (EXIT_SUCCESS);
	perror(msg);
	exit (EXIT_FAILURE);
}