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
	//memory free
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

int		ft_display_S(int fd, t_printf_elem *el)
{
	t_lstr	*lstr;
	wchar_t	*wstr;
	int		length;

	wstr = (wchar_t*)el->arg->ptr;
	lstr = ft_lstr_new_empty();
	while (*wstr && (el->precision_seted == 0 ||
			lstr->length + 4 <= el->precision))
		ft_putwchar(lstr, *wstr++);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, lstr->length);
	else
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, 0);
	ft_lstr_put_fd(lstr, fd);
	length = lstr->length;
	ft_lstr_destroy(&lstr);
	return (length);
}