NAME=libftprintf.a
SRCS=src/*.c
OBJS=*.o
LIBFT= lib/libft
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@mv $(LIBFT)/libft.a $(NAME)
	@gcc $(CFLAGS) -c $(SRCS) -I includes -I $(LIBFT)
	@ar rc $(NAME) $(OBJS)

clean:
	@make -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re