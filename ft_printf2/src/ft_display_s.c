#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_s(int fd, t_printf_elem *el)
{
	int		length;
	int		len;
	char	*str;

	//if (el-> length_mod == 'l')
	//	return (ft_display_ws(fd, el));
	length = 0;
	if (el->arg->ptr == 0)
		str = "(null)";
	else
		str = (char*)el->arg->ptr;
	len = (int)ft_strlen(str);
	if (el->precision_seted && el->precision < len)
		len = el->precision;
	if (el->flags & FT_PRINTF_MINUS)
	{
		
		length += ft_putstrn_fd(fd, str, len);
		return (length + ft_putcharn_fd(fd, ' ', el->width - len));
	}
	else
	{
		length += ft_putcharn_fd(fd, ' ', el->width - len);
		return (length + ft_putstrn_fd(fd, str, len));
	}
}