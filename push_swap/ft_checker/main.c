#include "libft.h"
#include "ft_stack.h"

int		ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (-1);
}

int		main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	int			result;

	if (argc == 1)
		return (ft_error());
	if (!ft_get_args(argc, argv, &a, &b))
		return (ft_error());
	if (!ft_do_commands(a, b))
	{
		ft_free_stacks(&a, &b);
		return (ft_error());
	}
	result = ft_check(a, b);
	ft_free_stacks(&a, &b);
	if (result)
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	return (0);
}