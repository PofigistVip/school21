
#include <string.h>
#include "libft.h"

void	ft_lstr_place_c(t_lstr *lstr, char c, int count, int index)
{
	if (lstr == NULL || count <= 0 || index < 0 || index > lstr->length)
		return ;
	if (lstr->length - index + count + 1 > lstr->capacity)
		if (ft_lstr_resize(lstr, lstr->length - index + count)  == NULL)
			return ;
	ft_memset(lstr->str + index, c, count);
}
