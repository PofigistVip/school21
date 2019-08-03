#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	check_brackets(char *str)
{
	char	stk[4096];
	int		i;

	i = -1;
	while (*str)
	{
		if (*str == '(' || *str == '[' || *str == '{')
			stk[++i] = *str;
		else if (*str == ')' || *str == ']' || *str == '}')
		{
			if (i == -1 ||
				(*str == ')' && stk[i] != '(') ||
				(*str == ']' && stk[i] != '[') ||
				(*str == '}' && stk[i] != '{'))
			{
				ft_putstr("Error\n");
				return ;
			}
			--i;
		}
		++str;
	}
	ft_putstr((i == -1) ? "OK\n" : "Error\n");
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
			check_brackets(argv[i]);
	}
	else
		ft_putchar('\n');
	return (0);
}