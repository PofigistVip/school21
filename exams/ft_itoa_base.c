#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	int		num;
	char	str_base[] = "0123456789ABCDEF";
	int		len;
	char	*result;

	len = 1;
	num = value;
	while (num /= base)
		++len;
	num = value;
	if (num < 0)
	{
		if (base == 10)
			++len;
		num = -num;
	}
	if ((result = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	result[len--] = 0;
	if (num == 0)
	{
		result[0] = '0';
		return (result);
	}
	while (num)
	{
		result[len--] = str_base[num % base];
		num /= base;
	}
	if (value < 0 && base == 10)
		result[0] = '-';
	return (result);
}

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(void)
{
	int		val;
	int		base;
	char	*str_val;

	val = 255;
	base = 2;
	str_val = ft_itoa_base(val, base);
	if (str_val)
	{
		ft_putstr(str_val);
		ft_putstr("\n");
		free(str_val);
	}
	return (0);
}