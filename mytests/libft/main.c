
#include <stdlib.h>
#include "libft.h"


#define CHECK(lstr, cmp) \
	ft_print(lstr); \
	if (strcmp(lstr->str, cmp) == 0) { \
		ft_setforeground(2); \
		ft_putstr(" [ OK ]");  } \
	else  { \
		ft_setforeground(1); \
		ft_putstr(" [FAIL]");  } \
	ft_setdefault_cols(1); \
	ft_lstr_destroy(&lstr);

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

	ft_putstr("===CREATING===\n");
	ft_putstr(" Empty lstr: ");
	lstr = ft_lstr_new_empty();
	CHECK(lstr, "");

	ft_putstr("\n www str: ");
	lstr = ft_lstr_new('w', 3);
	CHECK(lstr, "www");

	ft_putstr("\n Raw 'abcd': ");
	lstr = ft_lstr_new_raw("abcd");
	CHECK(lstr, "abcd");

	ft_putstr("\n===INSERTING===");
	ft_putstr("\n ==CHAR==\n");
	ft_putstr(" Insert to 0 'a' in empty: ");
	lstr = ft_lstr_new_empty();
	ft_lstr_insert_c(lstr, 'a', 0);
	CHECK(lstr, "a");

	ft_putstr("\n Insert to 0 'a' in 'bcd': ");
	lstr = ft_lstr_new_raw("bcd");
	ft_lstr_insert_c(lstr, 'a', 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n Insert to 2 'c' in 'abd': ");
	lstr = ft_lstr_new_raw("abd");
	ft_lstr_insert_c(lstr, 'c', 2);
	CHECK(lstr, "abcd");

	ft_putstr("\n Insert to 3 'd' in 'abc': ");
	lstr = ft_lstr_new_raw("abc");
	ft_lstr_insert_c(lstr, 'd', 3);
	CHECK(lstr, "abcd");

	ft_putstr("\n ==STRING==\n");
	ft_putstr(" Insert 'abcd' in empty: ");
	lstr = ft_lstr_new_empty();
	ft_lstr_insert_s(lstr, "abcd", 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n Insert to 0 'ab' in 'cd': ");
	lstr = ft_lstr_new_raw("cd");
	ft_lstr_insert_s(lstr, "ab", 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n Insert to 2 'cd' in 'ab': ");
	lstr = ft_lstr_new_raw("ab");
	ft_lstr_insert_s(lstr, "cd", 2);
	CHECK(lstr, "abcd");

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