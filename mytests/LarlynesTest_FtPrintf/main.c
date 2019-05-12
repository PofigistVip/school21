#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <limits.h>
#define LTEST_BUFF_SIZE 10000

int		oldstdout;
int		fd[2];
char	*bufs[2];
char	ltest_bufer0[LTEST_BUFF_SIZE + 1];
char	ltest_bufer1[LTEST_BUFF_SIZE + 1];
int		ltest_count = 0;
int		ltest_errors = 0;

void	ltest_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ltest_close_stdout(void)
{
	oldstdout = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
}

char	*ltest_get_stdout(int buff_no)
{
	int readed;

	int flags = fcntl(fd[0], F_GETFL, 0);
	fcntl(fd[0], F_SETFL, flags | O_NONBLOCK);
	fflush(stdout);
	bufs[buff_no][0] = 0;
	readed = read(fd[0], bufs[buff_no], LTEST_BUFF_SIZE);
	if (readed >= 0)
		bufs[buff_no][readed] = 0;
	return (bufs[buff_no]);
}

void	ltest_open_stdout()
{
	close(fd[0]);
	close(fd[1]);
	dup2(oldstdout, STDOUT_FILENO);
	close(oldstdout);
}

#define LTEST_PRINTF(...) \
{ \
	printf("#%d ", ltest_count); \
	fflush(stdout); \
	ltest_close_stdout(); \
	int 	ltest_std_printf = printf(__VA_ARGS__); \
	char	*ltest_std_str = ltest_get_stdout(0); \
	int 	ltest_ft_printf = ft_printf(__VA_ARGS__); \
	char	*ltest_ft_str = ltest_get_stdout(1); \
	int		ltest_ok; \
	ltest_open_stdout(); \
	++ltest_count; \
	ltest_ok = strcmp(ltest_std_str, ltest_ft_str) == 0 && ltest_std_printf == ltest_ft_printf; \
	if (ltest_ok) \
	{ \
		ltest_putstr("\033[32m[ OK ]\033[m"); \
	} \
	else \
	{ \
		++ltest_errors; \
		ltest_putstr("\033[31m[FAIL]\033[m"); \
	} \
	ltest_putstr("\tformat: "); \
	ltest_putstr(#__VA_ARGS__); \
	ltest_putstr("\n"); \
	if (ltest_ok == 0) \
	{ \
		printf("\tstd: '%s'(%d)\n\t ft: '%s'(%d)\n", ltest_std_str, ltest_std_printf, ltest_ft_str, ltest_ft_printf); \
		fflush(stdout); \
	} \
}

int		ft_printf(const char *format, ...);

#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
void	ltest_moulitest(void)
{
	LTEST_PRINTF("This is a simple test.");
	LTEST_PRINTF("This is a simple test.\nSecond sentence.\n");
	LTEST_PRINTF("");
	LTEST_PRINTF("\n");
	LTEST_PRINTF("%s", "abc");
	LTEST_PRINTF("111%s333", "222");
	LTEST_PRINTF("%s333", "222");
	LTEST_PRINTF("111%s", "222");
	LTEST_PRINTF("{%s}", 0);
	LTEST_PRINTF("{%s}", "");
	LTEST_PRINTF("111%s333%s555", "222", "444");
	LTEST_PRINTF("111%s333%s555%saaa%sccc", "222", "444", "666", "bbb");
	LTEST_PRINTF("%s%s%s%s%s", "1", "2", "3", "4", "5");
	LTEST_PRINTF("%d", 42);
	LTEST_PRINTF("%d", -42);
	LTEST_PRINTF("before %d after", 42);
	LTEST_PRINTF("%d%d%d%d%d", 1, -2, 3, -4, 5);
	LTEST_PRINTF("a%db%dc%dd", 1, -2, 3);
	LTEST_PRINTF("%d", INT_MAX);
	LTEST_PRINTF("%d", INT_MIN);
	{
	int i;
	LTEST_PRINTF("%p", &i);
	unsigned long l;
	LTEST_PRINTF("%p", &l);
	char *str;
	LTEST_PRINTF("%p", &str);
	}
	LTEST_PRINTF("%p", &strlen);
	LTEST_PRINTF("%p", 0);
	LTEST_PRINTF("%%");
	LTEST_PRINTF("aa%%bb");
	LTEST_PRINTF("%%%%%%%%%%");
	LTEST_PRINTF(".%%.%%.%%.%%.%%.%%.%%.%%.");
	LTEST_PRINTF("%");
	LTEST_PRINTF("% Zoooo");
	LTEST_PRINTF("{%}");
	LTEST_PRINTF("{% %}");
	LTEST_PRINTF("s: %s, p: %p, d:%d", "a string", &ltest_moulitest, 42);
	LTEST_PRINTF("%s%p%d%d%p%s%p%p%s", "a", &free, 1, 2, &malloc, "b", &free, &malloc, "c");
	LTEST_PRINTF("%S", L"米");
	LTEST_PRINTF("%S", L"我是一只猫。");
	LTEST_PRINTF("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	LTEST_PRINTF("a%Sb%sc%S", L"我", "42", L"猫");
	LTEST_PRINTF("{%S}", NULL);
	LTEST_PRINTF("%D", 0L);
	LTEST_PRINTF("%D", 1L);
	LTEST_PRINTF("%D", -1L);
	LTEST_PRINTF("%D", 42L);
	LTEST_PRINTF("%D", LONG_MAX);
	LTEST_PRINTF("%D", LONG_MIN);
	LTEST_PRINTF("Coucou les %D!", 42);
	LTEST_PRINTF("%i", 42);
	LTEST_PRINTF("%i", -42);
	LTEST_PRINTF("before %i after", 42);
	LTEST_PRINTF("%i%i%i%i%i", 1, -2, 3, -4, 5);
	LTEST_PRINTF("a%ib%ic%id", 1, -2, 3);
	LTEST_PRINTF("%o", 42);
	LTEST_PRINTF("before %o after", 42);
	LTEST_PRINTF("%o%o%o%o%o", 1, 100, 999, 42, 999988888);
	LTEST_PRINTF("a%ob%oc%od", 0, 55555, 100000);
	LTEST_PRINTF("%O", 42);
	LTEST_PRINTF("before %O after", 42);
	LTEST_PRINTF("%O%O%O%O%O", 1, 100, 999, 42, 999988888);
	LTEST_PRINTF("a%Ob%Oc%Od", 0, 55555, 100000);
	LTEST_PRINTF("%O", LONG_MAX);
	LTEST_PRINTF("%u", 42);
	LTEST_PRINTF("before %u after", 42);
	LTEST_PRINTF("%u%u%u%u%u", 1, 100, 999, 42, 999988888);
	LTEST_PRINTF("a%ub%uc%ud", 0, 55555, 100000);
	LTEST_PRINTF("%u", UINT_MAX);
	LTEST_PRINTF("%U", 42);
	LTEST_PRINTF("%U", ULONG_MAX / 2);
	LTEST_PRINTF("%U", ULONG_MAX);
	LTEST_PRINTF("%x", 42);
	LTEST_PRINTF("before %x after", 42);
	LTEST_PRINTF("%x%x%x%x%x", 1, 100, 999, 42, 999988888);
	LTEST_PRINTF("a%xb%xc%xd", 0, 55555, 100000);
	LTEST_PRINTF("%x, %x", 0, UINT_MAX);
	LTEST_PRINTF("%X", 42);
	LTEST_PRINTF("before %X after", 42);
	LTEST_PRINTF("%X%X%X%X%X", 1, 100, 999, 42, 999988888);
	LTEST_PRINTF("a%Xb%Xc%Xd", 0, 55555, 100000);
	LTEST_PRINTF("%X, %X", 0, UINT_MAX);
	LTEST_PRINTF("%c", 'c');
	LTEST_PRINTF("%c%c", '4', '2');
	LTEST_PRINTF("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \
%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\
%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
'.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';',
'<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e',
'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}');
	LTEST_PRINTF("%c", 0);
	LTEST_PRINTF("%C", 'c');
	LTEST_PRINTF("%C%C", '4', '2');
	LTEST_PRINTF("%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C \
%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C\
%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C",
' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
'.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';',
'<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e',
'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}');
	LTEST_PRINTF("%C", L'猫');
	LTEST_PRINTF("%C", L'δ');
	LTEST_PRINTF("%C", L'요');
	LTEST_PRINTF("%C", L'莨');
	LTEST_PRINTF("%C", L'ي');
	LTEST_PRINTF("%C", 0);
	LTEST_PRINTF("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");
	{
	char c;
	LTEST_PRINTF("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
	}
	LTEST_PRINTF("%ld%ld", 0, 42);
	LTEST_PRINTF("%ld", (long)INT_MAX + 1);
	LTEST_PRINTF("%ld", (long)INT_MIN - 1);
	LTEST_PRINTF("%ld", LONG_MAX);
	LTEST_PRINTF("%ld", LONG_MIN);
	LTEST_PRINTF("%li%li", 0, 42);
	LTEST_PRINTF("%li", (long)INT_MAX + 1);
	LTEST_PRINTF("%li", (long)INT_MIN - 1);
	LTEST_PRINTF("%li", LONG_MAX);
	LTEST_PRINTF("%li", LONG_MIN);
	LTEST_PRINTF("%lu, %lu", 0, ULONG_MAX);
	LTEST_PRINTF("%lo, %lo", 0, ULONG_MAX);
	LTEST_PRINTF("%lx, %lx", 0, ULONG_MAX);
	LTEST_PRINTF("%lX, %lX", 0, ULONG_MAX);
	LTEST_PRINTF("%lc, %lc", L'暖', L'ح');
	LTEST_PRINTF("%ls, %ls", L"暖炉", L"لحم خنزير");
	LTEST_PRINTF("%lO, %lO", 0, USHRT_MAX);
	LTEST_PRINTF("%lU, %lU", 0, USHRT_MAX);
	LTEST_PRINTF("%lD, %lD", 0, USHRT_MAX);
	LTEST_PRINTF("%lld%lld", 0, 42);
	LTEST_PRINTF("%lld", LLONG_MAX);
	LTEST_PRINTF("%lld", LLONG_MIN);
	LTEST_PRINTF("%lli%lli", 0, 42);
	LTEST_PRINTF("%lli", LLONG_MAX);
	LTEST_PRINTF("%lli", LLONG_MIN);
	LTEST_PRINTF("%llu, %llu", 0, ULLONG_MAX);
	LTEST_PRINTF("%llo, %llo", 0, ULLONG_MAX);
	LTEST_PRINTF("%llx, %llx", 0, ULLONG_MAX);
	LTEST_PRINTF("%llX, %llX", 0, ULLONG_MAX);
	LTEST_PRINTF("%llO, %llO", 0, USHRT_MAX);
	LTEST_PRINTF("%llU, %llU", 0, USHRT_MAX);
	LTEST_PRINTF("%llD, %llD", 0, USHRT_MAX);
	LTEST_PRINTF("%hd%hd", (short int)0, (short int)42);
	LTEST_PRINTF("%hd", SHRT_MAX);
	LTEST_PRINTF("%hd", SHRT_MIN);
	LTEST_PRINTF("%hi%hi", 0, 42);
	LTEST_PRINTF("%hi", SHRT_MAX);
	LTEST_PRINTF("%hi", SHRT_MIN);
	LTEST_PRINTF("%hu, %hu", 0, USHRT_MAX);
	LTEST_PRINTF("%ho, %ho", 0, USHRT_MAX);
	LTEST_PRINTF("%hx, %hx", 0, USHRT_MAX);
	LTEST_PRINTF("%hX, %hX", 0, USHRT_MAX);
	LTEST_PRINTF("%hO, %hO", 0, USHRT_MAX);
	LTEST_PRINTF("%hU, %hU", 0, USHRT_MAX);
	LTEST_PRINTF("%hD, %hD", 0, USHRT_MAX);
	LTEST_PRINTF("%hhd%hhd", 1, 42);
	LTEST_PRINTF("%hhd", CHAR_MAX);
	LTEST_PRINTF("%hhd", CHAR_MAX + 42);
	LTEST_PRINTF("%hhd", CHAR_MIN);
	LTEST_PRINTF("%hhd", CHAR_MIN - 42);
	LTEST_PRINTF("%hhi%hhi", 0, 42);
	LTEST_PRINTF("%hhd", CHAR_MAX);
	LTEST_PRINTF("%hhd", CHAR_MAX + 42);
	LTEST_PRINTF("%hhi", CHAR_MIN);
	LTEST_PRINTF("%hhi", CHAR_MIN - 42);
	LTEST_PRINTF("%hhu, %hhu", 0, UCHAR_MAX);
	LTEST_PRINTF("%hho, %hho", 0, UCHAR_MAX);
	LTEST_PRINTF("%hhx, %hhx", 0, UCHAR_MAX);
	LTEST_PRINTF("%hhX, %hhX", 0, UCHAR_MAX);
	LTEST_PRINTF("%hhu, %hhu", 0, UCHAR_MAX + 42);
	LTEST_PRINTF("%hho, %hho", 0, UCHAR_MAX + 42);
	LTEST_PRINTF("%hhx, %hhx", 0, UCHAR_MAX + 42);
	LTEST_PRINTF("%hhX, %hhX", 0, UCHAR_MAX + 42);
	LTEST_PRINTF("%hhO, %hhO", 0, USHRT_MAX);
	LTEST_PRINTF("%hhU, %hhU", 0, USHRT_MAX);
	LTEST_PRINTF("%hhD, %hhD", 0, USHRT_MAX);
	LTEST_PRINTF("%hhC, %hhC", 0, L'米');
	LTEST_PRINTF("%hhS, %hhS", 0, L"米米");
	LTEST_PRINTF("%jd%jd", 0, 42);
	LTEST_PRINTF("%jd", LLONG_MAX);
	LTEST_PRINTF("%jd", LLONG_MIN);
	LTEST_PRINTF("%ji%ji", 0, 42);
	LTEST_PRINTF("%ji", LLONG_MAX);
	LTEST_PRINTF("%ji", LLONG_MIN);
	LTEST_PRINTF("%ju, %ju", 0, ULLONG_MAX);
	LTEST_PRINTF("%jo, %jo", 0, ULLONG_MAX);
	LTEST_PRINTF("%jx, %jx", 0, ULLONG_MAX);
	LTEST_PRINTF("%jX, %jX", 0, ULLONG_MAX);
	LTEST_PRINTF("%jO, %jO", 0, USHRT_MAX);
	LTEST_PRINTF("%jU, %jU", 0, USHRT_MAX);
	LTEST_PRINTF("%jD, %jD", 0, USHRT_MAX);
	LTEST_PRINTF("%zd%zd", 0, 42);
	LTEST_PRINTF("%zd", LLONG_MAX);
	LTEST_PRINTF("%zi%zi", 0, 42);
	LTEST_PRINTF("%zi", LLONG_MAX);
	LTEST_PRINTF("%zu, %zu", 0, ULLONG_MAX);
	LTEST_PRINTF("%zo, %zo", 0, ULLONG_MAX);
	LTEST_PRINTF("%zx, %zx", 0, ULLONG_MAX);
	LTEST_PRINTF("%zX, %zX", 0, ULLONG_MAX);
	LTEST_PRINTF("%zO, %zO", 0, USHRT_MAX);
	LTEST_PRINTF("%zU, %zU", 0, USHRT_MAX);
	LTEST_PRINTF("%zD, %zD", 0, USHRT_MAX);
	LTEST_PRINTF("%lp", 42);
	LTEST_PRINTF("{%10d}", 42);
	LTEST_PRINTF("{%4d}", 10000);
	LTEST_PRINTF("{%30d}", 10000);
	LTEST_PRINTF("{%10d}", -42);
	LTEST_PRINTF("{%3c}", 0);
	LTEST_PRINTF("{%5p}", 0);
	LTEST_PRINTF("{%-15p}", 0);
	LTEST_PRINTF("{%-13p}", &strlen);
	LTEST_PRINTF("{%-12p}", &strlen);
	LTEST_PRINTF("{%10R}");
	LTEST_PRINTF("{%30S}", L"我是一只猫。");
	LTEST_PRINTF("{%-30S}", L"我是一只猫。");
	LTEST_PRINTF("{%-10d}", 42);
	LTEST_PRINTF("{%-4d}", 10000);
	LTEST_PRINTF("{%-30d}", 10000);
	LTEST_PRINTF("{%010d}", 42);
	LTEST_PRINTF("{%010d}", -42);
	LTEST_PRINTF("{%04d}", 10000);
	LTEST_PRINTF("{%030d}", 10000);
	LTEST_PRINTF("{%030x}", 0xFFFF);
	LTEST_PRINTF("{%030X}", 0xFFFF);
	LTEST_PRINTF("{%03c}", 0);
	LTEST_PRINTF("{%05s}", "abc");
	LTEST_PRINTF("{%030S}", L"我是一只猫。");
	LTEST_PRINTF("{%05p}", 0);
	LTEST_PRINTF("{%05p}", &ltest_moulitest);
	LTEST_PRINTF("{%-15Z}", 123);
	LTEST_PRINTF("%#o", 42);
	LTEST_PRINTF("%#o", 0);
	LTEST_PRINTF("%#o", INT_MAX);
	LTEST_PRINTF("%#O", 1);
	LTEST_PRINTF("%#x", 42);
	LTEST_PRINTF("%#x", 0);
	LTEST_PRINTF("%#x", INT_MAX);
	LTEST_PRINTF("%#X", 42);
	LTEST_PRINTF("%#X", 0);
	LTEST_PRINTF("%#X", INT_MAX);
	LTEST_PRINTF("%#c", 0);
	LTEST_PRINTF("%+d", 42);
	LTEST_PRINTF("%+d", -42);
	LTEST_PRINTF("%+i", 42);
	LTEST_PRINTF("%+i", -42);
	LTEST_PRINTF("%+c", 0);
	LTEST_PRINTF("%+C", 0);
	LTEST_PRINTF("%+o", 0);
	LTEST_PRINTF("%+o", 42);
	LTEST_PRINTF("%+O", 0);
	LTEST_PRINTF("%+O", 42);
	LTEST_PRINTF("[%+s]", 0);
	LTEST_PRINTF("[%+s]", "(null)");
	LTEST_PRINTF("%+O", 1);
	LTEST_PRINTF("% d", 9999);
	LTEST_PRINTF("% d", -9999);
	LTEST_PRINTF("% i", 9999);
	LTEST_PRINTF("% i", -9999);
	LTEST_PRINTF("% u", 9999);
	LTEST_PRINTF("{% c}", 0);
	LTEST_PRINTF("{% c}", 'a');
	LTEST_PRINTF("{% s}", NULL);
	LTEST_PRINTF("{% s}", "(null)");
	LTEST_PRINTF("{% s}", "");
	LTEST_PRINTF("{% C}", 0);
	LTEST_PRINTF("{% C}", L'a');
	LTEST_PRINTF("{% S}", NULL);
	LTEST_PRINTF("{% S}", L"(null)");
	LTEST_PRINTF("{% S}", L"");
	LTEST_PRINTF("{% +d}", 42);
	LTEST_PRINTF("{%+ d}", 42);
	LTEST_PRINTF("{%+03d}", 0);
	LTEST_PRINTF("{% 03d}", 0);
	LTEST_PRINTF("{%0-3d}", 0);
	LTEST_PRINTF("{%+03d}", 12);
	LTEST_PRINTF("{%+03d}", 123456);
	LTEST_PRINTF("{%03.2d}", 0);
	LTEST_PRINTF("%#.O", 0);
	LTEST_PRINTF("%.4d", 42);
	LTEST_PRINTF("%.4d", 424242);
	LTEST_PRINTF("%.4d", -424242);
	LTEST_PRINTF("%15.4d", 42);
	LTEST_PRINTF("%15.4d", 424242);
	LTEST_PRINTF("%8.4d", 424242424);
	LTEST_PRINTF("%15.4d", -42);
	LTEST_PRINTF("%15.4d", -424242);
	LTEST_PRINTF("%8.4d", -424242424);
	LTEST_PRINTF("%4.15d", 42);
	LTEST_PRINTF("%4.8d", 424242424);
	LTEST_PRINTF("%4.15d", -42);
	LTEST_PRINTF("%4.15d", -424242);
	LTEST_PRINTF("%4.8d", -424242424);
	LTEST_PRINTF("%.d, %.0d", 0, 0);
	LTEST_PRINTF("%.10d", -42);
	LTEST_PRINTF("%.4i", 42);
	LTEST_PRINTF("%15.4i", 42);
	LTEST_PRINTF("%4.15i", 42);
	LTEST_PRINTF("%.i, %.0i", 0, 0);
	LTEST_PRINTF("%.4u", 42);
	LTEST_PRINTF("%.4u", 424242);
	LTEST_PRINTF("%15.4u", 42);
	LTEST_PRINTF("%15.4u", 424242);
	LTEST_PRINTF("%8.4u", 424242424);
	LTEST_PRINTF("%4.15u", 42);
	LTEST_PRINTF("%4.15u", 424242);
	LTEST_PRINTF("%4.8u", 424242424);
	LTEST_PRINTF("%.u, %.0u", 0, 0);
	LTEST_PRINTF("%.4o", 42);
	LTEST_PRINTF("%.4o", 424242);
	LTEST_PRINTF("%15.4o", 42);
	LTEST_PRINTF("%15.4o", 424242);
	LTEST_PRINTF("%8.4o", 424242424);
	LTEST_PRINTF("%4.15o", 42);
	LTEST_PRINTF("%4.15o", 424242);
	LTEST_PRINTF("%4.8o", 424242424);
	LTEST_PRINTF("%.o, %.0o", 0, 0);
	LTEST_PRINTF("%.4O", 42);
	LTEST_PRINTF("%15.4O", 42);
	LTEST_PRINTF("%4.15O", 42);
	LTEST_PRINTF("%.o, %.0O", 0, 0);
	LTEST_PRINTF("%.4x", 42);
	LTEST_PRINTF("%.4x", 424242);
	LTEST_PRINTF("%15.4x", 42);
	LTEST_PRINTF("%15.4x", 424242);
	LTEST_PRINTF("%8.4x", 424242424);
	LTEST_PRINTF("%4.15x", 42);
	LTEST_PRINTF("%4.15x", 42424242);
	LTEST_PRINTF("%4.8x", 424242424);
	LTEST_PRINTF("%.x, %.0x", 0, 0);
	LTEST_PRINTF("%.4X", 42);
	LTEST_PRINTF("%.4X", 424242);
	LTEST_PRINTF("%15.4X", 42);
	LTEST_PRINTF("%15.4X", 424242);
	LTEST_PRINTF("%8.4X", 424242424);
	LTEST_PRINTF("%4.15X", 42);
	LTEST_PRINTF("%4.15X", 424242);
	LTEST_PRINTF("%4.8X", 424242424);
	LTEST_PRINTF("%.X, %.0X", 0, 0);
	LTEST_PRINTF("%.4s", "42");
	LTEST_PRINTF("%.4s", "42 is the answer");
	LTEST_PRINTF("%15.4s", "42");
	LTEST_PRINTF("%15.4s", "I am 42");
	LTEST_PRINTF("%15.4s", "42 is the answer");
	LTEST_PRINTF("%4.15s", "42");
	LTEST_PRINTF("%4.15s", "I am 42");
	LTEST_PRINTF("%4.15s", "42 is the answer");
	LTEST_PRINTF("%4.s", "42");
	LTEST_PRINTF("%.4S", L"我是一只猫。");
	LTEST_PRINTF("%15.4S", L"我是一只猫。");
	LTEST_PRINTF("%4.15S", L"我是一只猫。");
	LTEST_PRINTF("%4.S", L"我是一只猫。");
	LTEST_PRINTF("%4.1S", L"Jambon");
	LTEST_PRINTF("%.c", 0);
	LTEST_PRINTF("%.5c", 0);
	LTEST_PRINTF("%.5c", 42);
	LTEST_PRINTF("%.C", 0);
	LTEST_PRINTF("%.5C", 0);
	LTEST_PRINTF("%.5C", 42);
	LTEST_PRINTF("%.0p, %.p", 0, 0);
	LTEST_PRINTF("%.5p", 0);
	LTEST_PRINTF("%9.2p", 1234);
	LTEST_PRINTF("%9.2p", 1234567);
	LTEST_PRINTF("%2.9p", 1234);
	LTEST_PRINTF("%2.9p", 1234567);
	LTEST_PRINTF("%.3%");
	LTEST_PRINTF("%#.o, %#.0o", 0, 0);
	LTEST_PRINTF("%#.x, %#.0x", 0, 0);
	LTEST_PRINTF("%.p, %.0p", 0, 0);
	LTEST_PRINTF("{%05.c}", 0);
	LTEST_PRINTF("{%05.s}", 0);
	LTEST_PRINTF("{%05.%}", 0);
	LTEST_PRINTF("{%05.Z}", 0);
	LTEST_PRINTF("{%#.5x}", 1);
	LTEST_PRINTF("%#.3o", 1);
	LTEST_PRINTF("{%05.S}", L"42 c est cool");
	LTEST_PRINTF("%hhd - %hhd", SHRT_MAX - 42,  SHRT_MAX - 4200);
	LTEST_PRINTF("%zi", LLONG_MIN);
	LTEST_PRINTF("%zd", LLONG_MIN);
	LTEST_PRINTF("% p|%+p", 42, 42);
	LTEST_PRINTF("%u", -42);
	LTEST_PRINTF("%u", UINT_MAX + 1);
	LTEST_PRINTF("%U", ULONG_MAX + 1);
	LTEST_PRINTF("%c", 200);
	LTEST_PRINTF("% u|%+u", 42, 42);
	LTEST_PRINTF("%hhu / %hhu", SHRT_MAX - 42,  SHRT_MAX - 4200);
	LTEST_PRINTF("%o, %ho, %hho", -42, -42, -42);
	LTEST_PRINTF("%o", LONG_MAX);
	LTEST_PRINTF("%O", LONG_MIN);
	LTEST_PRINTF("% o|%+o", 42, 42);
	LTEST_PRINTF("%#.o", 42);
	LTEST_PRINTF("% x|%+x", 42, 42);
	LTEST_PRINTF("% X|%+X", 42, 42);
	LTEST_PRINTF("%*d", 5, 42);
	LTEST_PRINTF("{%*d}", -5, 42);
	LTEST_PRINTF("{%*d}", 0, 42);
	LTEST_PRINTF("{%*c}", 0, 0);
	LTEST_PRINTF("{%*c}", -15, 0);
	LTEST_PRINTF("{%.*d}", 5, 42);
	LTEST_PRINTF("{%.*d}", -5, 42);
	LTEST_PRINTF("{%.*d}", 0, 42);
	LTEST_PRINTF("{%.*s}", 5, "42");
	LTEST_PRINTF("{%.*s}", -5, "42");
	LTEST_PRINTF("{%.*s}", 0, "42");
	LTEST_PRINTF("{%*s}", 5, 0);
	LTEST_PRINTF("{%3*p}", 10, 0);
	LTEST_PRINTF("%*.*d", 0, 3, 0);
	LTEST_PRINTF("{%3*d}", 0, 0);
	LTEST_PRINTF("{%*3d}", 0, 0);
	LTEST_PRINTF("{%*3d}", 5, 0);
	LTEST_PRINTF("{%05.*d}", -15, 42);
	LTEST_PRINTF("{%f}{%F}", 1.42, 1.42);
	LTEST_PRINTF("{%f}{%F}", -1.42, -1.42);
	LTEST_PRINTF("{%f}{%F}", 1444565444646.6465424242242, 1444565444646.6465424242242);
	LTEST_PRINTF("{%f}{%F}", -1444565444646.6465424242242454654, -1444565444646.6465424242242454654);
	
}

void	ltest_main(void)
{
	//LTEST_PRINTF(0);
	LTEST_PRINTF("");
	LTEST_PRINTF("Larlyne was here");
	LTEST_PRINTF("String one\nString two");
	LTEST_PRINTF("\n");
	//%c
	LTEST_PRINTF("%c", 'l');
	LTEST_PRINTF("%#c", 'l');
	LTEST_PRINTF("%0c", 'l');
	LTEST_PRINTF("%-c", 'l');
	LTEST_PRINTF("% c", 'l');
	LTEST_PRINTF("%+c", 'l');
	LTEST_PRINTF("%#0- +c", 'l');
	LTEST_PRINTF("%20c", 'l');
	LTEST_PRINTF("%.20c", 'l');
	LTEST_PRINTF("%-20c", 'l');
	LTEST_PRINTF("%20.5c", 'l');
	LTEST_PRINTF("%.-5c", 'l');
	LTEST_PRINTF("%-20.-5c", 'l');
	LTEST_PRINTF("%c %c %c", 'l', 'a', 'r');
	LTEST_PRINTF("This is char '%c' :)", 'l');
	//%s
	LTEST_PRINTF("%s", 0);
	LTEST_PRINTF("%8s", 0);
	LTEST_PRINTF("%-8s", 0);
	LTEST_PRINTF("%.3s", 0);
	LTEST_PRINTF("%s", "Simple string");
	LTEST_PRINTF("This is %s", "char array");
	LTEST_PRINTF("%3s", "CutMe");
	LTEST_PRINTF("%4s", "CutMe");
	LTEST_PRINTF("%5s", "CutMe");
	LTEST_PRINTF("%6s", "CutMe");
	LTEST_PRINTF("%-6s", "CutMe");
	LTEST_PRINTF("%.3s", "CutMe");
	LTEST_PRINTF("%.4s", "CutMe");
	LTEST_PRINTF("%.5s", "CutMe");
	LTEST_PRINTF("%.6s", "CutMe");
	LTEST_PRINTF("%.-6s", "CutMe");
	LTEST_PRINTF("%20.5s", "CutMe");
	LTEST_PRINTF("%20.3s", "CutMe");
	LTEST_PRINTF("%-20.5s", "CutMe");
	LTEST_PRINTF("%10.s", "CutMe");
	LTEST_PRINTF("%-10.s", "CutMe");
	LTEST_PRINTF("%# +0-10.s", "CutMe");
	//%d
	LTEST_PRINTF("%d", 21);
	LTEST_PRINTF("School %d", 21);
	LTEST_PRINTF("School %d!", 21);
	LTEST_PRINTF("%4d", 21);
	LTEST_PRINTF("%4.3d", 21);
	LTEST_PRINTF("%-5.3d", 21);
	LTEST_PRINTF("%#4d", 21);
	LTEST_PRINTF("%0.0d", 21);
	LTEST_PRINTF("%d", 0);
	LTEST_PRINTF("%4d", 0);
	LTEST_PRINTF("%.d", 0);
	LTEST_PRINTF("%.0d", 0);
	LTEST_PRINTF("%-4d", 0);
	LTEST_PRINTF("%hhd", 4221);
	LTEST_PRINTF("%hd", 4221);
	LTEST_PRINTF("%ld", 4221);
	LTEST_PRINTF("%lld", LLONG_MAX);
	LTEST_PRINTF("%d", LONG_MIN);
	//%i
	LTEST_PRINTF("%i", 21);
	LTEST_PRINTF("School %i", 21);
	LTEST_PRINTF("School %i!", 21);
	LTEST_PRINTF("%4i", 21);
	LTEST_PRINTF("%4.3i", 21);
	LTEST_PRINTF("%-5.3i", 21);
	LTEST_PRINTF("%#4i", 21);
	LTEST_PRINTF("%0.0i", 21);
	LTEST_PRINTF("%i", 0);
	LTEST_PRINTF("%4i", 0);
	LTEST_PRINTF("%.i", 0);
	LTEST_PRINTF("%.0i", 0);
	LTEST_PRINTF("%-4i", 0);
	LTEST_PRINTF("%hhi", 4221);
	LTEST_PRINTF("%hi", 4221);
	LTEST_PRINTF("%li", 4221);
	LTEST_PRINTF("%lli", LLONG_MAX);
	LTEST_PRINTF("%i", LONG_MIN);
	LTEST_PRINTF("% lli", LLONG_MAX);
	//%u
	LTEST_PRINTF("%u", 0);
	LTEST_PRINTF("%u", 255);
	LTEST_PRINTF("%u", -1);
	LTEST_PRINTF("%hhu", -1);
	LTEST_PRINTF("%hu", -1);
	LTEST_PRINTF("%lu", -1);
	LTEST_PRINTF("%llu", -1);
	LTEST_PRINTF("%u", LONG_MAX);
	//%p
	LTEST_PRINTF("%p", 0);
	LTEST_PRINTF("%p", &oldstdout);
	LTEST_PRINTF("%p", &strlen);
	LTEST_PRINTF("%30p", &oldstdout);
	LTEST_PRINTF("%.15p", &oldstdout);
	LTEST_PRINTF("%30.15p", &oldstdout);
	LTEST_PRINTF("%-30p", &oldstdout);
	LTEST_PRINTF("%hp", &oldstdout);
}

int		main(void)
{
	bufs[0] = ltest_bufer0;
	bufs[1] = ltest_bufer1;
	
	ltest_moulitest();
	//
	printf("\n%d ошибок из %d тестов!\n", ltest_errors, ltest_count);
	return (0);
}
