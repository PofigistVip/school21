all:
	@make -C ../../ft_printf2 re
	@gcc -o ft_printf test.c -L ../../ft_printf2 -lftprintf -I ../../ft_printf2/includes -I ../../libft
	@./ft_printf
	@rm ft_printf
