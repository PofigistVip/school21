#include <unistd.h>
#include <wchar.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_display_c(int fd, t_printf_elem *el)
{
	int		i;
	int		width;
	char	space;
	char	symb;

	symb = (unsigned char)el->arg->val_i;
	width = el->width;
	if (width <= 1)
	{
		write(fd, &symb, 1);
		return (1);
	}
	i = 1;
	space = (el->flags & FT_PRINTF_ZERO) ? '0' : ' '; //Проверить работает ли флаг 0 в Линуксе
	if (el->flags & FT_PRINTF_MINUS)
	{
		write(fd, &symb, 1);
		while (i++ < width)
			write(fd, &space, 1);
		return (width);
	}
	while (i++ < width)
		write(fd, &space, 1);
	write(fd, &symb, 1);
	return (width);
}

int		ft_display_C(int fd, t_printf_elem *el)
{
	t_lstr	*lstr;
	int		len;

	lstr = ft_lstr_new_empty();
	ft_putwchar(lstr, el->arg->val_wc);
	if (el->flags & FT_PRINTF_MINUS)
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, 0);
	else
		ft_lstr_insert_c(lstr, ' ', el->width - lstr->length, lstr->length);
	ft_lstr_put_fd(lstr, fd);
	len = lstr->length;
	ft_lstr_destroy(&lstr);
	return (len);
}