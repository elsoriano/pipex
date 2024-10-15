/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:53 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/15 12:47:00 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_clean_cmd(char **cmd)
{
	int	j;

	j = 0;
	if (cmd[0])
		while (cmd[j])
			free(cmd[j++]);
	if (cmd)
		free(cmd);
}

int	ft_clear_exit(t_index *i, char *msg)
{
	if (i && i->fd[0])
		close (i->fd[0]);
	if (i && i->fd[1])
		close (i->fd[1]);
	if (i && i->cmd1)
		ft_clean_cmd(i->cmd1);
	if (i && i->cmd2)
		ft_clean_cmd(i->cmd2);
	if (i && i->path1)
		free(i->path1);
	if (i && i->path2)
		free(i->path2);
	if (!msg)
		exit (EXIT_SUCCESS);
	perror(msg);
	exit (EXIT_FAILURE);
}
