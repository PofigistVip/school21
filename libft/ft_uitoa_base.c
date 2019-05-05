

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_uitoa_base(unsigned long long int nbr, int base)
{
	unsigned long long int	n;
	int						len;
	char					*str;
	char					*base_str;

	base_str = "0123456789abcdef";
	len  = 1;
	n = nbr;
	while ((n /= base) != 0)
		++len;
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len > -1)
	{
		str[len--] = base_str[nbr % base];
		nbr /= base;
	}
	return (str);
}