

#include <string.h>
#include "libft.h"

void	ft_llist_clear(t_llist *llist, (*cont_destroy)(void*))
{
	if (llist == NULL || cont_destroy == NULL)
		return ;
	while (llist->count > 0)
		ft_llist_remove(llist, 0, cont_destroy);
}