FTPRINTF_PATH=/home/pofigist/Desktop/school21/ft_printf2
CFLAGS=-Wnonnull
all:
	@make -C $(FTPRINTF_PATH) re
	@gcc $(CFLAGS) -o ltest main.c -L $(FTPRINTF_PATH) -lftprintf
	@./ltest
	@rm -f ltest