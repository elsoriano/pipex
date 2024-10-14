/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:29:24 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/14 11:22:58 by rhernand         ###   ########.fr       */
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
	char	*path1;
	char	**cmd1;
	char	*path2;
	char	**cmd2;
}		t_index;
