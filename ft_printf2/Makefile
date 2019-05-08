NAME=libftprintf.a
SRCS=src/*.c
OBJS=*.o
LIBFT=../libft
CFLAGS=-Wall -Wextra -Werror

all: fclean $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@mv $(LIBFT)/libft.a $(NAME)
	@gcc $(CFLAGS) -c $(SRCS) -I includes -I $(LIBFT)
	@ar rc $(NAME) $(OBJS)
	@make -C $(LIBFT) clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY=all clean fclean 