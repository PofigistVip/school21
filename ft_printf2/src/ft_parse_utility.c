#include "ft_printf.h"

int		ft_parse_is_conv_spec(char c)
{
	return (c == '%' ||
			c == 'x' ||
			c == 'X' ||
			c == 's' ||
			c == 'c' ||
			c == 'o' ||
			c == 'd' ||
			c == 'i' ||
			c == 'u' ||
			c == 'U' ||
			c == 'p' ||
			c == 'O' ||
			c == 'D' ||
			c == 'C' ||
			c == 'S');
}

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
		return (c1);
	return (0);
}

char	ft_parse_flag(char **fmt)
{
	char	c;

	c = **fmt;
	if (c == '#')
		return (FT_PRINTF_SHARP);
	if (c == '0')
		return (FT_PRINTF_ZERO);
	if (c == '-')
		return (FT_PRINTF_MINUS);
	if (c == ' ')
		return (FT_PRINTF_SPACE);
	if (c == '+')
		return (FT_PRINTF_PLUS);
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
	*str = ptr - 1;
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