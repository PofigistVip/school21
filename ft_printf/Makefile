

NAME=libftprintf.a
TESTNAME=ft_print.o
CFLAGS=-Wall -Wextra -Werror
SRC=src/*.c
OBJ=*.o
LIBFT=lib/libft

all: $(NAME)

$(NAME): libft
	@gcc $(CFLAGS) -c $(SRC) -I $(LIBFT) -I includes
	@ar rc libft.a $(OBJ)
	@ranlib libft.a
	@mv libft.a $(NAME)



libft:
	@make -C $(LIBFT) re
	@cp $(LIBFT)/libft.a libft.a

clean:
	@make -C $(LIBFT) fclean
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
