#include <unistd.h>
#include "ft_printf.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

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
		return (ft_infnum_create_num(1, FT_INFNUM_SIZE));
	if (power == 1)
		return (ft_infnum_create_num(2, FT_INFNUM_SIZE));
	res = ft_infnum_create_num(2, FT_INFNUM_SIZE);
	copy = ft_infnum_create_num(2, FT_INFNUM_SIZE);
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
		return (ft_infnum_create_num(1, FT_INFNUM_SIZE));
	if (power == 1)
		return (ft_infnum_create_num(5, FT_INFNUM_SIZE));
	res = ft_infnum_create_num(5, FT_INFNUM_SIZE);
	copy = ft_infnum_create_num(5, FT_INFNUM_SIZE);
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
	inum	= ft_infnum_create_empty(FT_INFNUM_SIZE);
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

int		ft_subnormal_count_zeroes(int one_pos)
{
	double		dbl;
	int			cnt;
	uint64_t	fraction;

	fraction = (1ULL << one_pos);
	ft_memcpy(&dbl, &fraction, 8);
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
	if (min == FT_INFNUM_SIZE)
		ft_lstr_insert_c(lstr, '0', 1, 0);
	else
	{
		i = inum->max_pos;
		while (i > min)	
			ft_lstr_insert_c(lstr, inum->digits[i--], 1, lstr->length);
		ft_lstr_insert_c(lstr, inum->digits[min], 1, lstr->length);
	}
	return (lstr);
}

void	ft_zeros_shift(t_infnum *inum, int shift)
{
	int len;
	char	*digits;

	digits = (char*)malloc(FT_INFNUM_SIZE);
	ft_memset(digits, '0', FT_INFNUM_SIZE);
	len = inum->max_pos + 1;
	ft_memmove(digits + (FT_INFNUM_SIZE - len - shift), inum->digits, len);
	free(inum->digits);
	inum->digits = digits;
	ft_infnum_calc_max_pos(inum);
	inum->min_pos += FT_INFNUM_SIZE - len - shift;
}

t_lstr	*ft_get_decimal(int mant, uint64_t fraction)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;
	int			zeroes;
	t_lstr		*dec_part;

	pos = 0;
	if (mant == -1023 && fraction == (1ULL << 63))
		return (ft_lstr_new('0', 1));
		
	inum = ft_infnum_create_empty(FT_INFNUM_SIZE);
	inum->min_pos = FT_INFNUM_SIZE;
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
			zeroes = ft_count_zeroes(mant + 1023);//
			
			ft_zeros_shift(temp, (zeroes < 0) ? 0 : zeroes);
			if (temp->min_pos < inum->min_pos)
				inum->min_pos = temp->min_pos;
			inum = ft_infnum_add(inum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		++pos;
	}
	inum->max_pos = FT_INFNUM_SIZE - 1;
	dec_part = ft_infnum_get(inum);
	ft_infnum_destroy(&inum);
	return (dec_part);
}

int		ft_f_get_normal(int mant, uint64_t fraction, t_lstr **int_p, t_lstr **dec_p)
{
	*int_p = ft_get_integer(mant, fraction);
	*dec_p = ft_get_decimal(mant, fraction);
	return (0);
}

int		ft_f_get_subnormal(uint64_t fraction, t_lstr **int_p, t_lstr **dec_p)
{
	t_infnum	*inum;
	t_infnum	*temp;
	size_t		pos;
	int			zeroes;

	pos = 0;
	inum = ft_infnum_create_empty(FT_INFNUM_SIZE);
	inum->min_pos = FT_INFNUM_SIZE;
	int mant = -1022;
	while (pos < 53)
	{
		
		if (fraction & (1ULL << 63))
		{
			temp = ft_infnum_pow5(1022 + pos);
			zeroes = ft_subnormal_count_zeroes(53 - pos - 1);
			ft_zeros_shift(temp, (zeroes < 0) ? 0 : zeroes);
			if (temp->min_pos < inum->min_pos)
				inum->min_pos = temp->min_pos;
			inum = ft_infnum_add(inum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		++pos;
	}
	inum->max_pos = FT_INFNUM_SIZE - 1;
	*int_p = ft_lstr_new('0', 1);
	*dec_p = ft_infnum_get(inum);
	ft_infnum_destroy(&inum);
	return (0);
}


void	ft_f_round(t_lstr *int_p, t_lstr *dec_p, int precision)
{
	int i;
	char curr;

	//if (dec_p->str[precision] > '5' || (dec_p->str[precision] == '5' && (dec_p->str[precision - 1] - '0') % 2 == 1))
	if (dec_p->str[precision] >= '5' && dec_p->length - 1 != precision)
	{
		curr = 10;
		i = precision - 1;
		while (curr / 10 != 0 && i >= 0)
		{
			curr = (dec_p->str[i] - '0') + 1;
			dec_p->str[i] = (curr % 10) + '0';
			--i;
		}
		i = int_p->length - 1;
		while (curr / 10 != 0)
		{
			curr = (int_p->str[i] - '0') + 1;
			int_p->str[i] = (curr % 10) + '0';
			--i;
		}
	}
	ft_lstr_resize(dec_p, precision);
	dec_p->length = precision;
}

void	ft_prepare_nums(t_printf_elem *el, t_double_keeper *keeper)
{
	int		length;
	t_lstr	*int_part;
	t_lstr	*dec_part;

	int_part = keeper->int_part;
	dec_part = keeper->dec_part;
	if (keeper->sign)
		ft_lstr_insert_c(int_part, '-', 1, 0);
	length = int_part->length + el->precision + ((el->precision) ? 1 : 0);
	if (el->width > length && !(el->flags & FT_PRINTF_MINUS))
			ft_lstr_insert_c(int_part,(el->flags & FT_PRINTF_ZERO) ? '0' : ' ',
			el->width - length, ((el->flags & FT_PRINTF_ZERO) && keeper->sign)
			? 1 : 0);
	if (el->precision != 0)
	{
		if (el->precision >= dec_part->length)
			ft_lstr_insert_c(dec_part, '0', el->precision - dec_part->length, dec_part->length);
		else
			ft_f_round(int_part, dec_part, el->precision);
		ft_lstr_insert_c(dec_part, '.', 1, 0);
	}
	if (el->width > length && (el->flags & FT_PRINTF_MINUS))
		ft_lstr_insert_c(dec_part, ' ', el->width - length, dec_part->length);
}

int		ft_show_double(int fd, t_double_keeper *keeper)
{
	int		length;
	t_lstr	*int_part;
	t_lstr	*dec_part;

	int_part = keeper->int_part;
	dec_part = keeper->dec_part;
	ft_lstr_put_fd(int_part, fd);
	ft_lstr_put_fd(dec_part, fd);
	length = int_part->length + dec_part->length;
	ft_lstr_destroy(&int_part);
	ft_lstr_destroy(&dec_part);
	free(keeper);
	return (length);
}

void	ft_get_number(double val, t_printf_elem *el, t_double_keeper *keeper)
{
	int				mant;

	mant = keeper->mantissa - 1023;
	if (val != val)
	{
		keeper->int_part = ft_lstr_new_copy((el->conv_type == 'F') ? "NAN" : "nan");
		keeper->dec_part = ft_lstr_new_empty();
		el->precision = 0;
		el->flags = el->flags & (!FT_PRINTF_ZERO);
		return ;
	}
	if (mant == 1024)
	{
		keeper->int_part = ft_lstr_new_copy((el->conv_type == 'F') ? "INF" : "inf");
		keeper->dec_part = ft_lstr_new_empty();
		el->precision = 0;
		el->flags = el->flags & (!FT_PRINTF_ZERO);
		return ;
	}
	if (keeper->mantissa == 0)
		ft_f_get_subnormal(keeper->fraction, &(keeper->int_part), &(keeper->dec_part));
	else
		ft_f_get_normal(mant, keeper->fraction, &(keeper->int_part), &(keeper->dec_part));
}

void	ft_get_sign_mantissa_fraction(double val, t_double_keeper *keeper)
{
	uint64_t	sig;
	int64_t		manti;
	uint64_t	fract;

	ft_memcpy(&sig, &val, 8);
	sig = sig & (1ULL << 63);
	ft_memcpy(&manti, &val, 8);
	manti = ((unsigned long long int)(manti << 1)) >> 53;
	ft_memcpy(&fract, &val, 8);
	fract = (fract << 11) | ((manti != 0) ? (1ULL << 63) : 0);
	keeper->sign = sig;
	keeper->mantissa = manti;
	keeper->fraction = fract;
}


int		ft_display_fF(int fd, t_printf_elem *el)
{
	t_double_keeper	*keeper;

	keeper = (t_double_keeper*)malloc(sizeof(t_double_keeper));
	ft_get_sign_mantissa_fraction(el->arg->val_d, keeper);
	keeper->int_part = 0;
	keeper->dec_part = 0;
	ft_get_number(el->arg->val_d, el, keeper);
	ft_prepare_nums(el, keeper);
	return (ft_show_double(fd, keeper));
}
