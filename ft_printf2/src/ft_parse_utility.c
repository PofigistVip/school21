#include "ft_printf.h"

char	ft_parse_len_mod(char **fmt)
{
	char	c1;
	char	c2;
	
	c1 = **fmt;
	c2 = *((*fmt) + 1);
	if (c1 == 'h' && c2 == 'h')
	{
		++(*fmt);
		return ('H');
	}
	if (c1 == 'l' && c2 == 'l')
	{
		++(*fmt);
		return ('M');
	}
	if (c1 == 'h' ||
		c1 == 'l' ||
		c1 == 'L' ||
		c1 == 'q' ||
		c1 == 'j' ||
		c1 == 'z' ||
		c1 == 't')
		return (c);
	return (0);
}

char	ft_parse_flag(char **fmt)
{
	char	c;

	c = **fmt;
	if (c == 'c')
		return (c);
	return (0);
}

int		ft_parse_get_number(char **str)
{
	char	*ptr;
	int		number;

	number = 0;
	ptr = *str;
	while ('0' <= *ptr && *ptr <= '9')
	{
		number = number * 10 + (*ptr - '0');
		++ptr;
	}
	*str = ptr;
	return (number);
}

int		ft_parse_is_reference(char *str)
{
	while ('0' <= *str && *str <= '9')
	{
		++str;
	}
	return (*str == '$');
}