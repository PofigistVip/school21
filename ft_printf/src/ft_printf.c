
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int is_conversion_specifier(char c)
{
	return (c == 'd' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'x' || c == 'X' || c == 'e' || c == 'E'
		|| c == 'f' || c == 'F' || c == 'g' || c == 'G'
		|| c == 'a' || c == 'A' || c == 'c' || c == 's'
		|| c == 'C' || c == 'S' || c == '%');
}

int		ft_printf(const char *format, ...)
{
	int		i;
	int		n;
	int		count;

	i = 0;
	n = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (n != 0)
			{
				ft_putnchar(format + i - n - 1, n);
				count += n;
			}
			n = 0;
			while (!is_conversion_specifier(format[++i]))
			{
				
			}
		}
		else
			++n;
		++i;
	}
	return (count);
}