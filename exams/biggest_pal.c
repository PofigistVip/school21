#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstrn(char *str, int len)
{
	write(1, str, len);
}

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		++str;
		++len;
	}
	return (len);
}

void	solo_pal(char *str, int str_len, char **start, int *len)
{
	char	*st;
	char	*end;
	int		i;

	i = -1;
	while (++i < str_len)
	{
		st = str + i;
		end = str + i;
		while (*st == *end && st != str - 1 && end != '\0')
		{
			if (end - st + 1 >= *len)
			{
				*len = end - st + 1;
				*start = st;
			}
			--st;
			++end;
		}
	}
}

void	doubly_pal(char *str, int str_len, char **start, int *len)
{
	char	*st;
	char	*end;
	int		i;

	i = -1;
	while (++i < str_len - 1)
	{
		st = str + i;
		end = str + i + 1;
		while (*st == *end && st != str - 1 && end != '\0')
		{
			if (end - st + 1 >= *len)
			{
				*len = end - st + 1;
				*start = st;
			}
			--st;
			++end;
		}
	}
}

#include <stdio.h>

int		main(int argc, char **argv)
{
	char	*start;
	int		str_len;
	int		len;

	len = 0;
	start = (void*)0;
	if (argc == 2)
	{
		str_len = ft_strlen(argv[1]);
		if (str_len != 0)
		{
			solo_pal(argv[1], str_len, &start, &len);
			doubly_pal(argv[1], str_len, &start, &len);
			ft_putstrn(start, len);
		}
	}
	ft_putchar('\n');
	return (0);
}