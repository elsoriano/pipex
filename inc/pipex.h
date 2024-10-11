/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:29:24 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/11 16:07:32 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/inc/libft.h"

typedef struct s_index
{
	int		fd[2];
	int		pipe1[2];
	int		pipe2[2];
	int		pid;
	char	**cmd;
	int		i;
}		t_index;
