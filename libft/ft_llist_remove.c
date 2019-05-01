
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_llist_remove(t_llist *llist, size_t index, void (*cont_destroy)(void*))
{
	t_llist_elem	*elem;

	if (llist == NULL || cont_destroy == NULL || llist->count == 0 ||
		llist->count - 1 < index)
		return ;
	--llist->count;
	elem = llist->start;
	while (index-- != 0)
		elem = elem->next;
	if (index == 0)
	{
		llist->start = elem->next;
		elem->next->prev = NULL;
	}
	if (index == llist->count)
	{
		llist->end = elem->prev;
		elem->prev->next = NULL;
	}
	else if (index > 0) // && index != count
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	cont_destroy(elem->content);
	free(elem);
}