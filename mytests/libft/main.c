
#include "libft.h"

void	ft_print(t_lstr *lstr)
{
	ft_putchar('\t');
	ft_putchar('\'');
	ft_lstr_put(lstr);
	ft_putchar('\'');
	ft_putstr(" \tLength: ");
	ft_putnbr(lstr->length);
	ft_putstr(" \tCapacity: ");
	ft_putnbr(lstr->capacity);
}

int		ft_lstr_tests(void)
{
	t_lstr	*lstr;

	ft_putstr("Empty lstr: ");
	lstr = ft_lstr_new_empty();
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	ft_putstr("\nwww str: ");
	lstr = ft_lstr_new('w', 3);
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	ft_putstr("\nRaw 'abcd': ");
	lstr = ft_lstr_new_raw("abcd");
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	ft_putchar('\n');
}

int		main(void)
{
	ft_setcolors(0, 7);
	ft_putstr("Larlyne's Strings Test (LSTR):");
	ft_setdefault_cols(1);
	ft_putchar('\n');
	ft_lstr_tests();

	return (0);
}