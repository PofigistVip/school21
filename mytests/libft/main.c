
#include "libft.h"

void	ft_print(t_lstr *lstr)
{
	ft_putchar('\'');
	ft_lstr_put(lstr);
	ft_putchar('\'');
}

int		ft_lstr_tests(void)
{
	t_lstr	*lstr;

	ft_putstr("Empty lstr: ");
	lstr = ft_lstr_empty();
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	ft_putstr("\nwww str: ");
	lstr = ft_lstr_new('w', 3);
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	ft_putstr("\nRaw from 'abcd': ");
	lstr = ft_lstr_from_raw("abcd");
	ft_print(lstr);
	ft_lstr_destroy(&lstr);

	
}

int		main(void)
{
	ft_putstr("Larlyne's Strings Test (LSTR):\n");
	ft_lstr_tests();

	return (0);
}