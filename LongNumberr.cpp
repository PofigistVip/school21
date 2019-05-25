// LongNumber.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <stdlib.h>
#include <iostream>

/*
** FT_LONGNUMBER_SIZE - количество int'ов на число
** FT_LONGNUMBERDIG_ON_INT - количество разрядов в одном int (не больше 4)
**								больше может привести к ошибкам
** FT_LONGNUMBER_BASE - основа числа. Высчитывается по формуле:
**						10^FT_LONGNUMBER_DIG_ON_INT
*/
#define FT_LONGNUMBER_SIZE 100
#define FT_LONGNUMBER_DIG_ON_INT 4
#define FT_LONGNUMBER_BASE 10000

typedef struct	s_longnumber
{
	char	is_decimal;
	int		dec_end_on;
	int		digits[FT_LONGNUMBER_SIZE];
}				t_longnumber;

int				ft_lnum_calc(t_longnumber *lnum, int pos)
{
	int value;

	value = lnum->digits[pos];
	if (value < 0)
	{
		if (pos + 1 == FT_LONGNUMBER_SIZE)
		{
			return (0);
		}
			
		value = -value;
		lnum->digits[pos + 1] -= (value / FT_LONGNUMBER_BASE) + 1;
		lnum->digits[pos] = ((value / FT_LONGNUMBER_BASE) + 1) * FT_LONGNUMBER_BASE - value;
		return (ft_lnum_calc(lnum, pos + 1));
	}
	value = lnum->digits[pos] / FT_LONGNUMBER_BASE;
	if (value >= 1)
	{
		if (pos + 1 == FT_LONGNUMBER_SIZE)
		{
			return (0);
		}
		lnum->digits[pos + 1] += value;
		lnum->digits[pos] %= FT_LONGNUMBER_BASE;
		return (ft_lnum_calc(lnum, pos + 1));
	}
	return (1);
}

void			ft_lnum_destroy(t_longnumber **lnum)
{
	free(*lnum);
	*lnum = NULL;
}

t_longnumber	*ft_lnum_new_zero()
{
	t_longnumber	*lnum;

	lnum = (t_longnumber*)malloc(sizeof(t_longnumber));
	lnum->is_decimal = 0;
	lnum->dec_end_on = 0;
	memset(lnum->digits, 0, sizeof(lnum->digits));
	return (lnum);
}

t_longnumber	*ft_lnum_new_copy(t_longnumber *src)
{
	t_longnumber	*lnum;
	int				i;

	lnum = (t_longnumber*)malloc(sizeof(t_longnumber));
	lnum->is_decimal = src->is_decimal;
	lnum->dec_end_on = src->dec_end_on;
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
		lnum->digits[i] = src->digits[i];
	return (lnum);
}

t_longnumber	*ft_lnum_new_int(int number)
{
	t_longnumber	*lnum;

	lnum = ft_lnum_new_zero();
	lnum->digits[0] = number;
	ft_lnum_calc(lnum, 0);
	return (lnum);
}

int				ft_lnum_length(t_longnumber *lnum)
{
	int	i;
	int	length;
	int temp;

	length = 0;
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		if (lnum->digits[i] != 0)
		{
			temp = lnum->digits[i];
			length = 1;
			while ((temp /= 10) != 0)
				length++;
			length += i * FT_LONGNUMBER_DIG_ON_INT;
			break ;
		}
	}
	if (i == -1)
		length = 1;
	return (length);
}

int			ft_lnum_dec(t_longnumber *lnum)
{
	--lnum->digits[0];
	return (ft_lnum_calc(lnum, 0));
}

t_longnumber	*ft_lnum_add(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	int				i;

	lnum = ft_lnum_new_copy(a);
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		lnum->digits[i] += b->digits[i];
		ft_lnum_calc(lnum, i);
	}
	lnum->dec_end_on = (a->dec_end_on < b->dec_end_on) ? a->dec_end_on : b->dec_end_on;
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_sub(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	int				i;

	lnum = ft_lnum_new_copy(a);
	i = FT_LONGNUMBER_SIZE;
	while (--i >= 0)
	{
		lnum->digits[i] -= b->digits[i];
		ft_lnum_calc(lnum, i);
	}
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_mul(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	t_longnumber	*copy_a;
	t_longnumber	*copy_b;
	int				i;

	copy_b = ft_lnum_new_copy(b);
	if (!ft_lnum_dec(copy_b))
	{
		ft_lnum_destroy(&copy_b);
		return (ft_lnum_new_zero());
	}
	lnum = ft_lnum_new_copy(a);
	copy_a = ft_lnum_new_copy(a);
	while (ft_lnum_dec(copy_b))
		lnum = ft_lnum_add(lnum, copy_a, 1, 0);
	ft_lnum_destroy(&copy_a);
	ft_lnum_destroy(&copy_b);
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

t_longnumber	*ft_lnum_pow(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b)
{
	t_longnumber	*lnum;
	t_longnumber	*copy_a;
	t_longnumber	*copy_b;
	int				i;

	copy_a = ft_lnum_new_copy(a);
	copy_b = ft_lnum_new_copy(b);
	lnum = ft_lnum_new_int(1);
	while (ft_lnum_dec(copy_b))
		lnum = ft_lnum_mul(lnum, copy_a, 1, 0);
	ft_lnum_destroy(&copy_a);
	ft_lnum_destroy(&copy_b);
	if (dst_a)
		ft_lnum_destroy(&a);
	if (dst_b)
		ft_lnum_destroy(&b);
	return (lnum);
}

void			ft_lnum_make_decimal(t_longnumber **lnum, int shift)
{
	int		length;
	int		offset;
	int		big_offset;
	int		min_offset;
	t_longnumber	*supp;

	supp = ft_lnum_new_int(10);
	length = ft_lnum_length(*lnum);
	offset = FT_LONGNUMBER_SIZE * FT_LONGNUMBER_DIG_ON_INT - shift - length;
	big_offset = offset / FT_LONGNUMBER_DIG_ON_INT;
	min_offset = offset % FT_LONGNUMBER_DIG_ON_INT;
	//printf("Shift: %d, Length: %d, B: %d, L: %d\n", shift, length, big_offset, min_offset);
	(*lnum)->dec_end_on = big_offset;
	memmove((*lnum)->digits + big_offset, (*lnum)->digits, sizeof(int) * (FT_LONGNUMBER_SIZE - big_offset));
	while (min_offset--)
		*lnum = ft_lnum_mul(*lnum, supp, 1, 0);
	ft_lnum_destroy(&supp);
}

char			*ft_lnum_get(t_longnumber *lnum)
{
	char	*str;
	int		length;
	int		i;
	int		j;
	int		temp;

	length = ft_lnum_length(lnum);
	str = (char*)malloc(sizeof(char) * (length + 1));
	str[length--] = '\0';
	i = 0;
	while (length >= 0)
	{
		j = 0;
		temp = lnum->digits[i];
		while (length >= 0 && j < FT_LONGNUMBER_DIG_ON_INT)
		{
			str[length--] = (temp % 10) + '0';
			temp /= 10;
			++j;
		}
		++i;
	}
	return (str);
}

char			*ft_lnum_get_dec(t_longnumber *lnum)
{
	char	*str;
	int		length;
	int		i;
	int		j;
	int		temp;

	length = (FT_LONGNUMBER_SIZE - lnum->dec_end_on) * FT_LONGNUMBER_DIG_ON_INT;
	str = (char*)malloc(sizeof(char) * (length + 1));
	str[length--] = '\0';
	i = lnum->dec_end_on;
	while (length >= 0)
	{
		j = 0;
		temp = lnum->digits[i];
		while (length >= 0 && j < FT_LONGNUMBER_DIG_ON_INT)
		{
			str[length--] = (temp % 10) + '0';
			temp /= 10;
			++j;
		}
		++i;
	}
	return (str);
}

int main()
{
	t_longnumber	*lnum1;
	t_longnumber	*lnum2;
	t_longnumber	*lnum3;
	t_longnumber	*lnum4;
	char			*snum;

	
	int i = 0;
	while (i < 10)
	{
		lnum1 = ft_lnum_new_int(5);
		lnum2 = ft_lnum_new_int(3);
		lnum3 = ft_lnum_pow(lnum1, lnum2, 1, 1);
		ft_lnum_make_decimal(&lnum3, i);
		snum = ft_lnum_get_dec(lnum3);
			printf("%s - %d\n", snum, i++);
		ft_lnum_destroy(&lnum3);
	}
	

	
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
