/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:10:24 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/28 13:17:21 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	char	*format = "%d==%1$*2$d%d\n";
	char	*str1 = "Larlyne";
	char	*int1 = 19;

	printf("=-=-=-=-=\n");
	printf(format, int1, 4);
	printf("=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, int1, 4);
		printf("=-=-=-=-=\n");
	}
	return (0);
}
