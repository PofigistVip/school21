
#include <stdlib.h>
#include "libft.h"


#define CHECK_STR(str, cmp) \
	ft_putstr(str); \
	if (strcmp(str, cmp) == 0) { \
		ft_setforeground(2); \
		ft_putstr(" [ OK ]");  } \
	else  { \
		ft_setforeground(1); \
		ft_putstr(" [FAIL]");  } \
	ft_setdefault_cols(1); \
	free(str);

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

void	ft_utility_tests(void)
{
	char	*num;

	ft_putstr("===FT_UITOA_BASE===");
	ft_putstr("\n ==ZERO==\n");
	ft_putstr("  0 dec to bin:\t\t ");
	num = ft_uitoa_base(0, 2);
	CHECK_STR(num, "0");

	ft_putstr("\n  0 dec to oct:\t\t ");
	num = ft_uitoa_base(0, 8);
	CHECK_STR(num, "0");

	ft_putstr("\n  0 dec to dec:\t\t ");
	num = ft_uitoa_base(0, 10);
	CHECK_STR(num, "0");

	ft_putstr("\n  0 dec to hex:\t\t ");
	num = ft_uitoa_base(0, 16);
	CHECK_STR(num, "0");

	ft_putstr("\n ==BASE-1==\n");
	ft_putstr("  1 dec to bin:\t\t ");
	num = ft_uitoa_base(1, 2);
	CHECK_STR(num, "1");

	ft_putstr("\n  7 dec to oct:\t\t ");
	num = ft_uitoa_base(7, 8);
	CHECK_STR(num, "7");

	ft_putstr("\n  9 dec to dec:\t\t ");
	num = ft_uitoa_base(9, 10);
	CHECK_STR(num, "9");

	ft_putstr("\n  15 dec to hex:\t ");
	num = ft_uitoa_base(15, 16);
	CHECK_STR(num, "f");

	ft_putstr("\n ==BASE==\n");
	ft_putstr("  2 dec to bin:\t\t ");
	num = ft_uitoa_base(2, 2);
	CHECK_STR(num, "10");

	ft_putstr("\n  8 dec to oct:\t\t ");
	num = ft_uitoa_base(8, 8);
	CHECK_STR(num, "10");

	ft_putstr("\n  10 dec to dec:\t ");
	num = ft_uitoa_base(10, 10);
	CHECK_STR(num, "10");

	ft_putstr("\n  16 dec to hex:\t ");
	num = ft_uitoa_base(16, 16);
	CHECK_STR(num, "10");

	ft_putstr("\n ==256==\n");
	ft_putstr("  256 dec to bin:\t ");
	num = ft_uitoa_base(256, 2);
	CHECK_STR(num, "100000000");

	ft_putstr("\n  256 dec to oct:\t ");
	num = ft_uitoa_base(256, 8);
	CHECK_STR(num, "400");

	ft_putstr("\n  256 dec to dec:\t ");
	num = ft_uitoa_base(256, 10);
	CHECK_STR(num, "256");

	ft_putstr("\n  256 dec to hex:\t ");
	num = ft_uitoa_base(256, 16);
	CHECK_STR(num, "100");

	ft_putstr("\n ==125==\n");
	ft_putstr("  125 dec to bin:\t ");
	num = ft_uitoa_base(125, 2);
	CHECK_STR(num, "1111101");

	ft_putstr("\n  125 dec to oct:\t ");
	num = ft_uitoa_base(125, 8);
	CHECK_STR(num, "175");

	ft_putstr("\n  125 dec to dec:\t ");
	num = ft_uitoa_base(125, 10);
	CHECK_STR(num, "125");

	ft_putstr("\n  125 dec to hex:\t ");
	num = ft_uitoa_base(125, 16);
	CHECK_STR(num, "7d");

	ft_putchar('\n');
}

void	ft_lstr_tests(void)
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
	
	ft_putstr("\n  Insert 2'b' in 'a*a': ");
	lstr = ft_lstr_new_copy("aa");
	ft_lstr_insert_c(lstr, 'b', 2, 1);
	CHECK(lstr, "abba");

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
	ft_putstr("\n  Place 'c' to 3 in 'abdd': ");
	lstr = ft_lstr_new_copy("abdd");
	ft_lstr_place_c(lstr, 'c', 1, 2);
	CHECK(lstr, "abcd");

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
	ft_putstr("Larlyne's Utility Test:");
	ft_setdefault_cols(1);
	ft_putchar('\n');
	ft_utility_tests();

	ft_setcolors(0, 7);
	ft_putstr("Larlyne's Strings Test (LSTR):");
	ft_setdefault_cols(1);
	ft_putchar('\n');
	ft_lstr_tests();

	return (0);
}