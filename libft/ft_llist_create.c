/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:39:11 by larlyne           #+#    #+#             */
/*   Updated: 2019/04/30 11:39:13 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_llist		*ft_llist_create(size_t content_size)
{
	t_list	*list;

	if (content_size == 0)
		return (NULL);
	if ((list = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	list->content_size = content_size;
	list->count = 0;
	list->start = NULL;
	list->end = NULL;
	return (list);
}