NAME=libftprintf.a
SRCS=src/ft_printf.c
OBJS=*.o
LIBFT= lib/libft
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) -c $(SRCS) -I includes
	@ar rc $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re