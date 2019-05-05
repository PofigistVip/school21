

#include "libft.h"
#include "ft_printf.h"

void	ft_get_di_prefix(t_print_elem *el, char *nbr, t_lstr **prefix, t_lstr **num)
{
	*prefix = ft_lstr_new_empty();
	if (*nbr == '-')
	{
		ft_lstr_insert_c(*prefix, '-', 1, 0);
		++nbr;
	}
	else if (has_flag(el, 16))
		ft_lstr_insert_c(*prefix, '+', 1, 0);
	else if (has_flag(el, 8))
		ft_lstr_insert_c(*prefix, ' ', 1, 0);
	*num = ft_lstr_new_copy(nbr);
	if ((*num)->length < el->precision)
		ft_lstr_insert_c(*num, '0', el->precision - (*num)->length, 0);
}

void	ft_get_uoxX_prefix(t_print_elem *el, char *nbr, t_lstr **prefix, t_lstr **num)
{
	*prefix = ft_lstr_new_empty();
	*num = ft_lstr_new_copy(nbr);
	if (has_flag(el, 1))
	{
		if (el->conv_type == 'o')
			ft_lstr_insert_c(*prefix, '0', 1, 0);
		else if (el->conv_type == 'x' || el->conv_type == 'X')
			ft_lstr_insert_s(*prefix, "0x", 0);
	}
	if ((*num)->length < el->precision)
		ft_lstr_insert_c(*num, '0', el->precision - (*num)->length, 0);
}

void	ft_get_diuoxX(t_print_elem *el, t_lstr *prefix, t_lstr *num)
{
	ft_lstr_insert_s(el->str, prefix->str, 0);
	if (prefix->length + num->length >= el->width)
		ft_lstr_insert_s(el->str, num->str, el->str->length);
	else if (has_flag(el, 4))
	{
		ft_lstr_insert_s(el->str, num->str, el->str->length);
		ft_lstr_insert_c(el->str, ' ', el->width - prefix->length - num->length,
			el->str->length);
	}
	else
	{
		if (has_flag(el, 2))
			ft_lstr_insert_c(el->str, '0', el->width - prefix->length - num->length,
				el->str->length);
		else
			ft_lstr_insert_c(el->str, ' ', el->width - prefix->length - num->length, 0);
		ft_lstr_insert_s(el->str, num->str, el->str->length);
	}
	//ft_lstr_destroy(&prefix);
	//ft_lstr_destroy(&num);
}