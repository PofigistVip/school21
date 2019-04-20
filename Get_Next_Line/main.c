/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:56 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/20 14:09:56 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int		main(void)
{
	char	*line;
	int		result;
	int		fd;
	int		i;

	fd = open("text.txt", O_RDONLY);
	i = 0;
	while (1)
	{
		result = get_next_line(fd, &line, i++);
		printf("(%d): '%s'\n", result, line);
		if (result == 0 || result == -1)
			break ;
	}
	close(fd);
	return (0);
}
