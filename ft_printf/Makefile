

NAME=libprintf.a
TESTNAME=ft_print.o
SRC=src/*.c
LIBFT=lib/libft/

all: libft
	@make -o $(TESTNAME) -I includes -I $(LIBFT) $(SRC) -L $(LIBFT) -lft
libft:
	@make -C $(LIBFT) re

.PHONY: all libft
