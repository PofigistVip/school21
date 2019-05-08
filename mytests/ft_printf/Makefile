all:
	@make -C ../../ft_printf2 re
	@gcc -o ft_printf test.c -L ../../ft_printf2 -I ../../ft_printf2/includes -I ../../libft -lftprintf
	@./ft_printf
	@rm ft_printf

debug:
	@make -C ../../ft_printf2 re
	@gcc -o ft_printf test.c -D LDEBUG -L ../../ft_printf2 -I ../../ft_printf2/includes -I ../../libft -lftprintf
	@./ft_printf
	@rm ft_printf