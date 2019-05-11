#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int			ft_parse_num_or_pos(int number, int *pos)
{
	if (number >= 0)
		return (number);
	return ((*pos)++);
}

void			ft_parse_str_elem(t_printf_elem *el, char **fmt, char *ptr)
{
	int		len;
	char	*raw;

	el->conv_type = 0;
	len = ptr - *fmt;
	raw = (char*)malloc(len + 1);
	ft_memcpy(raw, *fmt, len);
	*(raw + len) = '\0';
	el->raw_str = raw;
	*fmt = ptr;
}

int				ft_parse_get_pos(char **fmt)
{
	char	*ptr;
	int		number;

	ptr = *fmt;
	if (ft_parse_is_reference(ptr + 1))
	{
		++ptr;
		number = ft_parse_get_number(&ptr);
		*fmt = ptr;
		return(number);
	}
	return (-1);
}

void			ft_parse_spec_inner(t_printf_elem *el, char **fmt, int *pos)
{
	char	*ptr;
	char	support;
	int		number;

	ptr = *fmt;
	while (*ptr && !ft_parse_is_conv_spec(*ptr))
	{
		if ((support = ft_parse_len_mod(&ptr)) != 0)
		{
			el->length_mod = support;
		}
		else if ((support = ft_parse_flag(&ptr)) != 0)
		{
			el->flags |= support;
		}
		else if (*ptr == '*')
		{
			number = ft_parse_get_pos(&ptr);
			el->width_pos = ft_parse_num_or_pos(number, pos);
			el->width_seted = 1;
		}
		else if ('1' <= *ptr && *ptr <= '9')
		{
			el->width = ft_parse_get_number(&ptr);
			el->width_seted = 1;
		}
		else if (*ptr == '.')
		{
			++ptr;
			if (*ptr == '*')
			{
				++ptr;
				number = ft_parse_get_pos(&ptr);
				el->precision_pos = ft_parse_num_or_pos(number, pos);
			}
			else
			{
				el->precision = ft_parse_get_number(&ptr);
			}
			el->precision_seted = 1;
		}
		++ptr;
	}
	*fmt = ptr;
}

t_printf_elem	*ft_parse_spec(char **fmt, int *pos)
{
	char			*ptr;
	t_printf_elem	*el;
	char			use_pos;

	ptr = *fmt;
	++ptr;
	el = ft_printf_elem_new();
	use_pos = 0;
	if (ft_parse_is_reference(ptr))
	{
		el->pos = ft_parse_get_number(&ptr);
		*pos = el->pos + 1;
		++ptr;
	}
	else
	{
		use_pos = 1;
	}
	ft_parse_spec_inner(el, &ptr, pos);
	if (*ptr)
	{
		if (use_pos)
		{
			el->pos = (*pos)++;
		}
		el->conv_type = *ptr;
		*fmt = ptr + 1;
	}
	else //формат не закончен в конце fmt
	{
		ft_parse_str_elem(el, fmt, ptr);
	}
	return (el);
}