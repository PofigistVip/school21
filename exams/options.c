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

void	ft_help(void)
{
	ft_putstr("options: abcdefghijklmnopqrstuvwxyz\n");
}

void	ft_show_binary(int data)
{
	int i;

	i = -1;
	while (++i < 32)
	{
		if (data & (0b10000000000000000000000000000000 >> i))
			ft_putchar('1');
		else
			ft_putchar('0');
		if (i && (i + 1) % 8 == 0)
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	int		data;
	int		i;
	int		j;

	if (argc == 1)
	{
		ft_help();
		return (0);
	}
	data = 0;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j] && 'a' <= argv[i][j] && argv[i][j] <= 'z')
				if (argv[i][j] == 'h')
				{
					ft_help();
					return (0);
				}
				else
					data |= (0b00000000000000000000000000000001 << (argv[i][j] - 'a'));
			if (argv[i][j])
			{
				ft_putstr("Invalid option\n");
				return (0);
			}
		}
	}
	ft_show_binary(data);
	return (0);
}
