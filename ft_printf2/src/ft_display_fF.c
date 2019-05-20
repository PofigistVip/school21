#include <unistd.h>
#include "ft_printf.h"
#include <stdint.h>
#include <stdlib.h>

void	show_binary(void *vptr, int count)
{
	char	*ptr;
	unsigned char	mask;

	ptr = (char*)vptr;
	ptr += count / 8 - 1;
	while (count > 0)
	{
		
		mask = (1 << 7);
		while (mask != 0 && count > 0)
		{
			if (*ptr & mask)
				ft_putchar('1');
			else
				ft_putchar('0');
			--count;
			mask = mask >> 1;
		}
		--ptr;
	}
}
#include <stdio.h>

t_infnum	*ft_infnum_pow2(int power)
{
	t_infnum	*res;
	t_infnum	*temp;
	t_infnum	*copy;

	if (power == 0)
		return (ft_infnum_create_num(1, 320));
	if (power == 1)
		return (ft_infnum_create_num(2, 320));
	res = ft_infnum_create_num(2, 320);
	copy = ft_infnum_create_num(2, 320);
	--power;
	while (power > 0)
	{
		temp = ft_infnum_mul(res, copy);
		ft_infnum_destroy(&res);
		res = temp;
		--power;
	}
	ft_infnum_destroy(&copy);
	return (res);
}

t_infnum	*ft_infnum_pow5(int power)
{
	t_infnum	*res;
	t_infnum	*temp;
	t_infnum	*copy;

	if (power == 0)
		return (ft_infnum_create_num(1, 320));
	if (power == 1)
		return (ft_infnum_create_num(5, 320));
	res = ft_infnum_create_num(5, 320);
	copy = ft_infnum_create_num(5, 320);
	--power;
	while (power > 0)
	{
		temp = ft_infnum_mul(res, copy);
		ft_infnum_destroy(&res);
		res = temp;
		--power;
	}
	ft_infnum_destroy(&copy);
	return (res);
}

t_lstr	*ft_get_integer(int mant, uint64_t fraction)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;
	t_lstr		*int_part;

	pos = 0;
	inum	= ft_infnum_create_empty(320);
	while (mant >= 0 && pos < 64)
	{
		if (fraction & (1ULL << 63))
		{
			temp = ft_infnum_pow2(mant);
			inum = ft_infnum_add(inum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		pos++;
	}
	int_part = ft_infnum_get(inum);
	ft_infnum_destroy(&inum);
	return (int_part);
}

int		ft_count_zeroes(int mantissa)
{
	double		dbl;
	int			cnt;
	uint64_t	mant;

	mant = (((uint64_t)mantissa) << 52);
	ft_memcpy(&dbl, &mant, 8);
	cnt = -1;
	while (dbl < 1)
	{
		dbl *= 10;
		++cnt;
	}
	return (cnt);
}

t_lstr		*ft_infnum_get(t_infnum *inum)
{
	t_lstr	*lstr;
	size_t	i;
	size_t	min;

	lstr = ft_lstr_new_empty();
	min = inum->min_pos;
	i = inum->max_pos;
	while (i > min)	
		ft_lstr_insert_c(lstr, inum->digits[i--], 1, lstr->length);
	ft_lstr_insert_c(lstr, inum->digits[min], 1, lstr->length);
	return (lstr);
}

void	ft_zeros_shift(t_infnum *inum, int shift)
{
	int len;
	char	*digits;

	digits = (char*)malloc(320);
	ft_memset(digits, '0', 320);
	len = inum->max_pos + 1;
	ft_memmove(digits + (320 - len - shift), inum->digits, len);
	free(inum->digits);
	inum->digits = digits;
	ft_infnum_calc_max_pos(inum);
	inum->min_pos += 320 - len - shift;
}

t_lstr	*ft_get_decimal(int mant, uint64_t fraction)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;
	int			zeroes;
	t_lstr		*dec_part;

	pos = 0;
	inum = ft_infnum_create_empty(320);
	inum->min_pos = 320;
	while (mant >= 0 && pos < 64)
	{
		fraction = fraction << 1;
		mant--;
		++pos;
	}
	while (pos < 64)
	{
		if (fraction & (1ULL << 63))
		{
			temp = ft_infnum_pow5(-mant);
			zeroes = ft_count_zeroes(mant + 1023);
			ft_zeros_shift(temp, (zeroes < 0) ? 0 : zeroes);
			if (temp->min_pos < inum->min_pos)
				inum->min_pos = temp->min_pos;
			inum = ft_infnum_add(inum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		++pos;
	}
	inum->max_pos = 319;
	dec_part = ft_infnum_get(inum);
	ft_infnum_destroy(&inum);
	return (dec_part);
}



int		ft_display_fF(int fd, t_printf_elem *el)
{
	double	val;
	char	sign;
	long long int	mantissa;
	int				mant;
	uint64_t		fraction;
	t_lstr			*int_part;
	t_lstr			*dec_part;
	int				length;

	length = 0;
	val = el->arg->val_d;
	sign = (val < 0) ? -1 : 1;
	ft_memcpy(&mantissa, &val, 8);
	mantissa = ((unsigned long long int)(mantissa << 1)) >> 53;
	ft_memcpy(&fraction, &val, 8);
	fraction = (fraction << 11) | (1ULL << 63);
	//normal way
	mant = mantissa - 1023;
	int_part = ft_get_integer(mant, fraction);
	length += int_part->length;
	ft_lstr_put_fd(int_part, fd);
	if (el->precision > 0)
	{
		dec_part = ft_get_decimal(mant, fraction);
		if (el->precision >= dec_part->length)
			ft_lstr_insert_c(dec_part, '0', el->precision - dec_part->length, dec_part->length);
		else
		{
			ft_lstr_resize(dec_part, el->precision);
			dec_part->length = el->precision;
		}
		ft_lstr_insert_c(dec_part, '.', 1, 0);
		ft_lstr_put_fd(dec_part, fd);
		length += dec_part->length;
	}
	
	
	
	(void)mant;
	(void)fd;
	(void)sign;
	return (length);
}
