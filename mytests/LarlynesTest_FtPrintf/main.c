#include <unistd.h>
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
int		main(void)
{
	bufs[0] = ltest_bufer0;
	bufs[1] = ltest_bufer1;
	
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
	//
	printf("\n%d ошибок из %d тестов!\n", ltest_errors, ltest_count);
	return (0);
}
