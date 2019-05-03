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
	char	*format = "Hmm... %c\n";
	char	*str1 = "Larlyne";
	int		int1 = 1090;

	printf("=-=-=-=-=\n");
	printf(format, int1);
	printf("=-=-=-=-=\n");
	if (argc == 1)
	{
		ft_printf(format, int1);
		printf("=-=-=-=-=\n");
	}
	return (0);
}
