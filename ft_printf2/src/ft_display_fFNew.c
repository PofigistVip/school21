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

t_longnumber	*ft_lnum_pow2(int power)
{
	t_longnumber	*res;
	t_longnumber	*temp;
	t_longnumber	*copy;

	if (power == 0)
		return (ft_lnum_new_int(1));
	if (power == 1)
		return (ft_lnum_new_int(2));
	res = ft_lnum_new_int(2);
	copy = ft_lnum_new_int(2);
	--power;
	while (power > 0)
	{
		temp = ft_lnum_mul(res, copy, 1, 0);
		res = temp;
		--power;
	}
	ft_lnum_destroy(&copy);
	return (res);
}

t_longnumber	*ft_lnum_pow5(int power)
{
	t_longnumber	*res;
	t_longnumber	*copy;

	if (power == 0)
		return (ft_lnum_new_int(1));
	if (power == 1)
		return (ft_lnum_new_int(5));
	res = ft_lnum_new_int(5);
	copy = ft_lnum_new_int(5);
	--power;
	while (power > 0)
	{
		res = ft_lnum_mul(res, copy, 1, 0);
		--power;
	}
	ft_lnum_destroy(&copy);
	return (res);
}

t_lstr	*ft_get_integer(int mant, __uint128_t fraction)
{
	t_longnumber	*lnum;
	t_longnumber	*temp;
	t_longnumber	*temp_temp;
	size_t		pos;
	t_lstr		*int_part;

	fraction = fraction >> 64;
	pos = (64 - mant - 1 < 0) ? 0 : 64 - mant - 1;
	lnum	= ft_lnum_new_zero();
	temp = 0;
	temp_temp = ft_lnum_new_int(2);
	mant -= 63 - pos;
	while (pos < 64)
	{
		if (!temp)
			temp = ft_lnum_pow2(mant);
		else
			temp = ft_lnum_mul(temp, temp_temp, 1, 0);
		if (fraction & ((__uint128_t)1 << pos))
		{
			lnum = ft_lnum_add(lnum, temp, 1, 0);
		}
		++mant;
		pos++;
	}
	int_part = ft_lstr_new_raw(ft_lnum_get(lnum));
	ft_lnum_destroy(&lnum);
	ft_lnum_destroy(&temp);
	ft_lnum_destroy(&temp_temp);
	return (int_part);
}

int		ft_count_zeroes(int mantissa)
{
	long double		dbl;
	int			cnt;
	__int128_t	mant;

	mant = (((__uint128_t)mantissa) << 64) | ((__uint128_t)1 << 63);
	ft_memcpy(&dbl, &mant, 10);
	// ft_putstr("\nM");
	// show_binary(&dbl, 80);
	// ft_putchar('\n');
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

	fraction = ((__uint128_t)1 << one_pos);
	ft_memcpy(&dbl, &fraction, 10);
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

t_lstr	*ft_get_decimal(int mant, __uint128_t fraction)
{
	t_longnumber *lnum;
	t_longnumber *temp;
	t_longnumber *temp_temp;
	t_longnumber *tmp;
	int		pos;
	int			zeroes;
	t_lstr		*dec_part;

	pos = 0;
	
	if (mant >= 64)
		return (ft_lstr_new('0', 1));
		
	lnum = ft_lnum_new_zero();
	ft_lnum_make_decimal(&lnum, 0);
	temp_temp = ft_lnum_new_int(5);
	temp = 0;
	if (mant >= 0)
	{
		pos = 62 - mant;
		mant = -1;
	}
	else
		pos = 63;
	fraction = fraction >> 64;
	while (pos >= 0)
	{
		if (!temp)
			temp = ft_lnum_pow5(-mant);
		else
			temp = ft_lnum_mul(temp, temp_temp, 1, 0);
		if (fraction & ((__uint128_t)1 << pos))
		{
			tmp = ft_lnum_new_copy(temp);
			zeroes = ft_count_zeroes(mant + 16383);//
			ft_lnum_make_decimal(&tmp, zeroes);
			lnum = ft_lnum_add(lnum, tmp, 1, 1);
			
		}
		--mant;
		--pos;
	}
	dec_part = ft_lstr_new_raw(ft_lnum_get_dec(lnum));
	ft_lnum_destroy(&lnum);
	ft_lnum_destroy(&temp);
	ft_lnum_destroy(&temp_temp);
	
	return (dec_part);
}

int		ft_f_get_normal(int mant, __uint128_t fraction, t_lstr **int_p, t_lstr **dec_p)
{
	*int_p = ft_get_integer(mant, fraction);
	*dec_p = ft_get_decimal(mant, fraction);
	return (0);
}

int		ft_f_get_subnormal(__uint128_t fraction, t_lstr **int_p, t_lstr **dec_p)
{
	t_longnumber	*lnum;
	t_longnumber	*temp;
	size_t		pos;
	int			zeroes;

	pos = 0;
	lnum = ft_lnum_new_zero();
	ft_lnum_make_decimal(&lnum, 0);
	int mant = -16382;
	while (pos < 64)
	{
		
		if (fraction & ((__uint128_t)1 << 127))
		{
			temp = ft_lnum_pow5(16382 + pos);
			zeroes = ft_subnormal_count_zeroes(64 - pos - 1);
			ft_lnum_make_decimal(&temp, zeroes);
			lnum = ft_lnum_add(lnum, temp, 1, 1);
		}
		fraction = fraction << 1;
		--mant;
		++pos;
	}
	*int_p = ft_lstr_new('0', 1);
	*dec_p = ft_lstr_new_raw(ft_lnum_get_dec(lnum));
	ft_lnum_destroy(&lnum);
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
	else if (el->flags & (FT_PRINTF_PLUS | FT_PRINTF_SPACE))
		ft_lstr_insert_c(int_part, (el->flags & FT_PRINTF_PLUS) ? '+' : ' ', 1, 0);
	length = int_part->length + el->precision + ((el->precision ||
		el->flags & FT_PRINTF_SHARP) ? 1 : 0);
	if (el->width > length && !(el->flags & FT_PRINTF_MINUS))
			ft_lstr_insert_c(int_part,(el->flags & FT_PRINTF_ZERO) ? '0' : ' ',
			el->width - length, ((el->flags & FT_PRINTF_ZERO) && (keeper->sign ||
			(el->flags & (FT_PRINTF_PLUS | FT_PRINTF_SPACE)) ? 1 : 0)));
	if (el->precision == 0)
	{
		ft_lstr_resize(dec_part, 0);
		dec_part->length = 0;
		ft_f_round(int_part, dec_part, 0);
		if (el->flags & FT_PRINTF_SHARP)
			ft_lstr_insert_c(dec_part, '.', 1, 0);
	}
	else
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

void	ft_get_number(long double val, t_printf_elem *el, t_double_keeper *keeper)
{
	int			mant;

	mant = keeper->mantissa - 16383;
	if (val != val)
	{
		keeper->int_part = ft_lstr_new_copy((el->conv_type == 'F') ? "NAN" : "nan");
		keeper->dec_part = ft_lstr_new_empty();
		el->precision = 0;
		el->flags = el->flags & (!FT_PRINTF_ZERO);
		return ;
	}
	if (mant == 16384)
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

void	ft_get_sign_mantissa_fraction(long double val, t_double_keeper *keeper)
{
	__uint128_t	sig;
	__int128_t	manti;
	__uint128_t	fract;

	ft_memcpy(&sig, &val, 10);
	sig = sig & ((__uint128_t)1 << 79);
	ft_memcpy(&manti, &val, 10);
	manti = ((__uint128_t)(manti << 49)) >> 113;
	ft_memcpy(&fract, &val, 10);
	fract = (fract << 64);// | ((manti != 0) ? (1ULL << 63) : 0);
	keeper->sign = sig;
	keeper->mantissa = manti;
	keeper->fraction = fract;
	// ft_putchar('\n');
	// ft_putchar('F');
	// show_binary(&(keeper->fraction), 128);
	// ft_putchar('\n');
}


int		ft_display_fF(int fd, t_printf_elem *el)
{
	t_double_keeper	*keeper;

	// ft_putstr("\nN");
	// show_binary(&(el->arg->val_d), 80);
	// ft_putchar('\n');
	keeper = (t_double_keeper*)malloc(sizeof(t_double_keeper));
	ft_get_sign_mantissa_fraction(el->arg->val_d, keeper);
	keeper->int_part = 0;
	keeper->dec_part = 0;
	ft_get_number(el->arg->val_d, el, keeper);
	ft_prepare_nums(el, keeper);
	return (ft_show_double(fd, keeper));
}
