#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_puthex(unsigned char c)
{
	char alpha[] = "0123456789abcdef";

	ft_putchar(alpha[c / 16]);
	ft_putchar(alpha[c % 16]);
}

void	print_hex(const void *addr, int i, int step)
{
	int			missed_cols;
	const unsigned char	*caddr;

	
	missed_cols = 16 - step;
	caddr = (const unsigned char*)addr;
	while (step > 0)
	{
		if (step > 1)
		{
			ft_puthex(caddr[i++]);
			ft_puthex(caddr[i++]);
			ft_putchar(' ');
			step -= 2;
		}
		else
		{
			ft_puthex(caddr[i++]);
			ft_putchar(' ');
			--step;
		}
	}
	while (missed_cols > 0)
	{
		if (missed_cols > 1)
		{
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
			missed_cols -= 2;
		}
		else
		{
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
			--missed_cols;
		}
		
	}
}

void	print_view(const void *addr, int i, int step)
{
	const unsigned char	*caddr;

	caddr = (const unsigned char*)addr;
	while (step-- > 0)
	{
		if (32 <= caddr[i] && caddr[i] <= 127)
			ft_putchar(caddr[i]);
		else
			ft_putchar('.');
		++i;
	}
}

void	print_memory(const void *addr, size_t size)
{
	size_t	i;
	int		step;

	i = 0;
	while (i < size)
	{
		step = (size - i < 16) ? size - i : 16;
		print_hex(addr, i, step);
		print_view(addr, i, step);
		ft_putchar('\n');
		i += step;
	}
}

int		main(void)
{
	int		tab[10] = { 0, 23, 150, 255, 12, 16, 21, 42};
	
	print_memory(tab, sizeof(tab));
	return (0);
}