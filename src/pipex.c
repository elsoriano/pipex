/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:28:49 by rhernand          #+#    #+#             */
/*   Updated: 2024/10/05 19:35:13 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_infile(char *infile)
{
	
}

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		perror("You have entered an invalid number of arguments");
		return (1);
	}
	ft_check_infile(argv[1]);
}