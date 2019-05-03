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
	char	*format = "Hello, %s. You are welcome!\nYou're %d years old\n";
	char	*str1 = "Larlyne";
	char	*int1 = 19;

	printf("=-=-=-=-=\n");
	printf(format, str1, int1);
	printf("=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, str1, int1);
		printf("=-=-=-=-=\n");
	}
	return (0);
}
