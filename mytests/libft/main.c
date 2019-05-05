
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
	lstr = ft_lstr_new_copy("abcd");
	CHECK(lstr, "abcd");

	ft_putstr("\n===INSERTING===");
	ft_putstr("\n ==CHAR==\n");
	ft_putstr("  Insert to 0 'a' in empty: ");
	lstr = ft_lstr_new_empty();
	ft_lstr_insert_c(lstr, 'a', 1, 0);
	CHECK(lstr, "a");

	ft_putstr("\n  Insert to 0 'a' in 'bcd': ");
	lstr = ft_lstr_new_copy("bcd");
	ft_lstr_insert_c(lstr, 'a', 1, 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n  Insert to 2 'c' in 'abd': ");
	lstr = ft_lstr_new_copy("abd");
	ft_lstr_insert_c(lstr, 'c', 1, 2);
	CHECK(lstr, "abcd");

	ft_putstr("\n  Insert to 3 'd' in 'abc': ");
	lstr = ft_lstr_new_copy("abc");
	ft_lstr_insert_c(lstr, 'd', 1, 3);
	CHECK(lstr, "abcd");

	ft_putstr("\n  Insert 2'b' in 'aa*': ");
	lstr = ft_lstr_new_copy("aa");
	ft_lstr_insert_c(lstr, 'b', 2, 2);
	CHECK(lstr, "aabb");

	ft_putstr("\n  Insert 2'b' in '*aa': ");
	lstr = ft_lstr_new_copy("aa");
	ft_lstr_insert_c(lstr, 'b', 2, 0);
	CHECK(lstr, "bbaa");

	ft_putstr("\n ==STRING==\n");
	ft_putstr("  Insert 'abcd' in empty: ");
	lstr = ft_lstr_new_empty();
	ft_lstr_insert_s(lstr, "abcd", 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n  Insert to 0 'ab' in 'cd': ");
	lstr = ft_lstr_new_copy("cd");
	ft_lstr_insert_s(lstr, "ab", 0);
	CHECK(lstr, "abcd");

	ft_putstr("\n  Insert to 2 'cd' in 'ab': ");
	lstr = ft_lstr_new_copy("ab");
	ft_lstr_insert_s(lstr, "cd", 2);
	CHECK(lstr, "abcd");

	ft_putstr("\n  2 symb from 'cdcd' to 'ab*': ");
	lstr = ft_lstr_new_copy("ab");
	ft_lstr_insert_sn(lstr, "cdcd", 2, 2);
	CHECK(lstr, "abcd");

	ft_putstr("\n===PLACE===");
	ft_putstr("\n ==CHAR==");
	ft_putstr("\n  Place 2'a' to 0 in 'bbbb': ");
	lstr = ft_lstr_new_copy("bbbb");
	ft_lstr_place_c(lstr, 'a', 2, 0);
	CHECK(lstr, "aabb");

	ft_putstr("\n  Place 2'a' to 2 in 'bbbb': ");
	lstr = ft_lstr_new_copy("bbbb");
	ft_lstr_place_c(lstr, 'a', 2, 2);
	CHECK(lstr, "bbaa");

	ft_putstr("\n  Full 'a' all 'abcd':\t ");
	lstr = ft_lstr_new_copy("abcd");
	ft_lstr_place_c(lstr, 'a', lstr->length, 0);
	CHECK(lstr, "aaaa");

	ft_putstr("\n  Place 4'a' to 0 in 'bc': ");
	lstr = ft_lstr_new_copy("bc");
	ft_lstr_place_c(lstr, 'a', 4, 0);
	CHECK(lstr, "aaaa");

	ft_putstr("\n  Place 4'c' in empty:\t ");
	lstr = ft_lstr_new_empty();
	ft_lstr_place_c(lstr, 'c', 4, 0);
	CHECK(lstr, "cccc");

	ft_putstr("\n===MEMORY===");
	ft_putstr("\n Capacity minimization (5->3): ");
	char	*str = ft_strnew(6);
	ft_memmove(str, "abcd", 5);
	lstr = ft_lstr_new_raw(str);
	lstr->str[2] = '\0';
	lstr->length = (int)ft_strlen(str);
	ft_lstr_minimize(lstr);
	CHECK(lstr, "ab");

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