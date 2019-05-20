// InfinityNumbers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_printf.h"



t_infnum	*ft_infnum_create_empty(size_t size)
{
	t_infnum	*inum;

	if (size == 0)
		return (NULL);
	inum = (t_infnum*)malloc(sizeof(t_infnum));
	inum->digits = (char*)malloc(size * sizeof(char));
	memset(inum->digits, '0', size);
	inum->size = size;
	inum->sign = 0;
	inum->max_pos = 0;
	inum->min_pos = 0;
	return (inum);
}

void		ft_infnum_destroy(t_infnum **inum)
{
	free((*inum)->digits);
	free(*inum);
	*inum = NULL;
}

void		ft_infnum_calc_max_pos(t_infnum *inum)
{
	size_t	pos;

	if (!inum)
		return ;
	pos = inum->size - 1;
	while (pos > 0)
	{
		if (inum->digits[pos] != '0')
			break ;
		--pos;
	}
	inum->max_pos = pos;
}

void		*ft_memalloc(size_t n)
{
	void	*ptr;
	
	ptr = malloc(n);
	memset(ptr, 0, n);
	return (ptr);
}

char		*ft_itoa(int n)
{
	char	sign;
	char	size;
	int		num;
	char	*str;

	num = n;
	size = (num < 0) ? 2 : 1;
	while (num >= 10 || num <= -10)
	{
		size++;
		num /= 10;
	}
	if ((str = (char*)ft_memalloc(size + 1)) == NULL)
		return (NULL);
	sign = (n < 0) ? -1 : 1;
	if (n < 0)
		*str = '-';
	while (n >= 10 || n <= -10)
	{
		str[size - 1] = (n % 10) * sign + '0';
		--size;
		n /= 10;
	}
	str[size - 1] = (n % 10) * sign + '0';
	return (str);
}

size_t		ft_strlen(const char *s)
{
	char	*ptr;

	ptr = (char*)s;
	while (*ptr++)
		;
	return ((size_t)(ptr - s - 1));
}

void		ft_infnum_set_digits(t_infnum *inum, char *str, int min_pos)
{
	int			len;
	int			i;

	if (min_pos < 0)
		return ;
	len = (int)ft_strlen(str);
	i = -1;
	while (++i < len)
		inum->digits[min_pos + i] = str[len - i - 1];
}

t_infnum	*ft_infnum_create_copy(t_infnum *inum)
{
	t_infnum	*res;

	if ((res = ft_infnum_create_empty(inum->size)) == NULL)
		return (NULL);
	res->sign = inum->sign;
	res->max_pos = inum->max_pos;
	memcpy(res->digits, inum->digits, inum->size);
	return (res);
}

t_infnum	*ft_infnum_create_num(int number, size_t size)
{
	t_infnum	*inum;
	char		*str_num;

	if ((inum = ft_infnum_create_empty(size)) == NULL)
		return (NULL);
	if ((str_num = ft_itoa(number)) == NULL)
	{
		ft_infnum_destroy(&inum);
		return (NULL);
	}

	ft_infnum_set_digits(inum, str_num, 0);
	free(str_num);
	ft_infnum_calc_max_pos(inum);
	return (inum);
}

int			ft_infnum_pos_add(t_infnum *inum, char digit, size_t pos)
{
	char	current;

	if (pos > inum->size - 1)
		return (0);
	current = (inum->digits[pos] - '0') + (digit - '0');
	inum->digits[pos] = (current % 10) + '0';
	if (current / 10 > 0)
		ft_infnum_pos_add(inum, '1', pos + 1);
	else
		ft_infnum_calc_max_pos(inum);
	return (1);
}

int			ft_infnum_pos_sub(t_infnum *inum, char digit, size_t pos)
{
	char	current;

	if (pos > inum->size - 1)
		return (0);
	current = 10 + (inum->digits[pos] - '0') - (digit - '0');
	inum->digits[pos] = (current % 10) + '0';
	if (current < 10)
		ft_infnum_pos_sub(inum, '1', pos + 1);
	else
		ft_infnum_calc_max_pos(inum);
	return (1);
}

//int			ft_infnum_pos_mul(t_infnum *inum, char digit, size_t pos)
//{
//	char	current;
//
//	if (pos > inum->size - 1)
//		return (0);
//	current = (inum->digits[pos] - '0') * (digit - '0');
//	inum->digits[pos] = (current % 10) + '0';
//	if (current >= 10)
//
//}

t_infnum	*ft_infnum_add(t_infnum *a, t_infnum *b, int destroy_a, int destroy_b)
{
	t_infnum	*res;
	size_t		pos;

	if ((res = ft_infnum_create_copy(a)) == NULL)
		return (NULL);
	pos = 0;
	while (pos <= b->size - 1)
	{
		if (b->digits[pos] != '0')
			ft_infnum_pos_add(res, b->digits[pos], pos);
		++pos;
	}
	res->min_pos = a->min_pos;
	if (destroy_a)
		ft_infnum_destroy(&a);
	if (destroy_b)
		ft_infnum_destroy(&b);
	return (res);
}

t_infnum	*ft_infnum_mul(t_infnum *a, t_infnum *b)
{
	t_infnum	*res;
	t_infnum	*copy;
	t_infnum	*bcopy;
	t_infnum	*temp;
	
	if ((a->max_pos == 0 && a->digits[0] == '0') ||
		(b->max_pos == 0 && b->digits[0] == '0'))
		return (ft_infnum_create_num(0, a->size));
	if ((copy = ft_infnum_create_copy(a)) == NULL)
		return (NULL);
	if ((bcopy = ft_infnum_create_copy(b)) == NULL)
		return (NULL);
	if ((res = ft_infnum_create_empty(a->size)) == NULL)
		return (NULL);
	res->sign = (a->sign == b->sign) ? 0 : 1;
	copy->sign = 0;
	while (bcopy->max_pos > 0 || bcopy->digits[0] != '0')
	{
		temp = ft_infnum_add(res, copy, 0, 0);
		ft_infnum_destroy(&res);
		res = temp;
		ft_infnum_pos_sub(bcopy, '1', 0);
	}
	ft_infnum_destroy(&copy);
	ft_infnum_destroy(&bcopy);
	return (res);
}

t_infnum	*ft_infnum_pow(t_infnum *inum, t_infnum *power)
{
	t_infnum	*res;
	t_infnum	*temp;
	t_infnum	*copy;

	if (inum->max_pos == 0)
	{
		if (inum->digits[0] == '0')
			return (ft_infnum_create_num(0, inum->size));
		if (inum->digits[0] == '1')
			return (ft_infnum_create_num(1, inum->size));
	}
	if (power->max_pos == 0 && power->digits[0] == '0')
		return (ft_infnum_create_num(1, inum->size));
	if ((copy = ft_infnum_create_copy(inum)) == NULL)
		return (NULL);
	if ((res = ft_infnum_create_copy(inum)) == NULL)
		return (NULL);
	ft_infnum_pos_sub(power, '1', 0);
	while (power->max_pos > 0 || power->digits[0] != '0')
	{
		temp = ft_infnum_mul(res, copy);
		ft_infnum_destroy(&res);
		res = temp;
		ft_infnum_pos_sub(power, '1', 0);
	}
	ft_infnum_destroy(&copy);
	return (res);
}

#include <limits.h>


void			ft_infnum_show(t_infnum *inum)
{
	size_t	i;
	size_t	min;

	min = inum->min_pos;
	i = inum->max_pos;
	while (i > min)
		putchar(inum->digits[i--]);
	putchar(inum->digits[min]);
}

// int main()
// {
// 	t_infnum	*inum = ft_infnum_create_num(5, 1000);
// 	t_infnum	*cnum = ft_infnum_create_num(256, 20);
// 	t_infnum	*res = ft_infnum_pow(inum, cnum);
// 	ft_infnum_show(res);
// 	return (0);
// }

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
