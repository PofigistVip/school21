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
	//bugs:
	//%20.3-sA\n
	//%20-sA\n
	//проверить флаги после чисел на MacOS!
	char	*format = "'%-20.3s'\n";
	char	*str1 = "Larlyne";
	char	char1 = 42;
	int		int1 = 20;
	int		int2 = 3;

	printf("=-=-=-=-=\n");
	printf(format, str1);
	printf("=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, str1);
		printf("=-=-=-=-=\n");
	}
	return (0);
}
