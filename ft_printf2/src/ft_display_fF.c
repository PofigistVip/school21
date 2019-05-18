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

void	ft_get_integer(int mant, uint64_t fraction)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;

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
	ft_infnum_show(inum);
	ft_infnum_destroy(&inum);
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

void			ft_infnum_dec_show(t_infnum *inum)
{
	size_t	i;

	i = 319;
	while (i > 0)
		putchar(inum->digits[i--]);
	putchar(inum->digits[0]);
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
}

void	ft_get_decimal(int mant, uint64_t fraction)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;
	int			zeroes;

	pos = 0;
	inum = ft_infnum_create_empty(320);
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
			inum = ft_infnum_add(inum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		++pos;
	}
	ft_infnum_dec_show(inum);
	
	ft_infnum_destroy(&inum);
}



int		ft_display_fF(int fd, t_printf_elem *el)
{
	double	val;
	char	sign;
	long long int	mantissa;
	int				mant;
	uint64_t		fraction;

	val = el->arg->val_d;
	sign = (val < 0) ? -1 : 1;
	ft_memcpy(&mantissa, &val, 8);
	mantissa = ((unsigned long long int)(mantissa << 1)) >> 53;
	ft_memcpy(&fraction, &val, 8);
	fraction = (fraction << 11) | (1ULL << 63);
	//normal way
	mant = mantissa - 1023;
	ft_get_integer(mant, fraction);
	ft_putchar('.');
	ft_get_decimal(mant, fraction);
	(void)mant;
	(void)fd;
	(void)sign;
	return (0);
}




// 1000000000, offset = 5
// 11000000000
// integer: 110000
// decimal: 
// 
// 
// 
// 
// 
// 
// 
// 
