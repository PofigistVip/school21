#include "libft.h"
#include "ft_printf.h"

int		ft_display_raw(int fd, t_printf_elem *el)
{
	ft_putstr_fd(el->raw_str, fd);
	return ((int)ft_strlen(el->raw_str));
}