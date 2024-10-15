/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:29:24 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/15 12:14:13 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/inc/libft.h"

typedef struct s_index
{
	int		fd[2];
	int		pipe1[2];
	int		pid;
	char	*path1;
	char	**cmd1;
	char	*path2;
	char	**cmd2;
}		t_index;

int		ft_clear_exit(t_index *i, char *msg);
char	*ft_found_path(char *paths, char *cmd);
char	*ft_paths(t_index *i, char *cmd, char **envp);
void	ft_exec(t_index *i, char **envp);
void	ft_open_files(t_index *i, char *infile, char *outfile);
int		main(int argc, char **argv, char **envp);

#endif