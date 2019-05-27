/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:46:43 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/27 18:46:53 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_printf_arg	*ft_arg_new(void)
{
	t_printf_arg	*arg;

	arg = (t_printf_arg*)malloc(sizeof(t_printf_arg));
	ft_bzero(arg, sizeof(t_printf_arg));
	return (arg);
}
