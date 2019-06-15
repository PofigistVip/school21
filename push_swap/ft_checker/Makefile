CFLAGS=-Wall -Wextra -Werror
LIBFT=../lib/libft
all:
	@make -C $(LIBFT) re
	@gcc $(CFLAGS) -o checker *.c -L $(LIBFT) -I $(LIBFT) -lft
