

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_lstr	*ft_lstr_new(char c, size_t n)
{
	t_lstr	*lstr;

	if ((lstr = (t_lstr*)malloc(sizeof(t_lstr))) == NULL)
		return (NULL);
	if ((lstr->str = ft_strnew(n)) == NULL)
	{
		free(lstr);
		return (NULL);
	}
	ft_memset(lstr->str, c, n);
	lstr->length = n;
	lstr->capacity = n + 1;
	return (lstr);
}