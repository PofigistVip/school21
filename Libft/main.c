#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		main(void)
{
	char	num[] = "9999999999999999999999999";
	printf("St: %d\n", atoi(num));
	printf("Ft: %d\n", ft_atoi(num));
	return (0);
}