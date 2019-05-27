NAME=libftprintf.a
SRC_FILES=ft_display_c_big_c.c \
			ft_display_di.c \
			ft_display_f_big_f.c \
			ft_display_f_big_f_part.c \
			ft_display_f_big_f_part2.c \
			ft_display_f_big_f_part3.c \
			ft_display_perc.c \
			ft_display_raw.c \
			ft_display_s_big_s_unknown.c \
			ft_display_u_big_u_p.c \
			ft_display_x_big_x_o_big_o.c \
			ft_display.c \
			ft_get_args.c \
			ft_get_args_utility.c \
			ft_lnum.c \
			ft_lnum_math.c \
			ft_lnum_math2.c \
			ft_lnum_memory.c \
			ft_parse_spec.c \
			ft_parse_spec_utility.c \
			ft_parse_utility.c \
			ft_parse.c \
			ft_push_args.c \
			ft_wchar.c \
			ft_printf.c
SRCS=$(addprefix src/,$(SRC_FILES))
OBJS=$(SRC_FILES:.c=.o)
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
