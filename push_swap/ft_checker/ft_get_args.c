#include <string.h>
#include "ft_stack.h"
#include "libft.h"

/*
** Необходима проверка на переполнение
*/

int		ft_create_stacks(t_stack **a, t_stack **b, int size)
{
	if ((*a = ft_stack_new(size)) == NULL)
		return (0);
	if ((*b = ft_stack_new(size)) == NULL)
	{
		ft_stack_free(a);
		return (0);
	}
	return (1);
}

int		ft_free_stacks(t_stack **a, t_stack **b)
{
	ft_stack_free(a);
	ft_stack_free(b);
	return (0);
}

int		ft_get_args(int argc, char **argv, t_stack **a, t_stack **b)
{
	int			i;
	int			numb;

	if (!ft_create_stacks(a, b, argc - 1))
		return (0);
	i = argc - 1;
	while (i > 0)
	{
		if (ft_isint(argv[i]))
		{
			numb = ft_atoi(argv[i]);
			if (ft_stack_contains(*a, numb))
				i = -1;
			else
				ft_stack_push(*a, numb);
		}
		else
			i = -1;
		if (i == -1)
			break ;
	}
	if (i == -1)
		return (ft_free_stacks(a, b));
	return (1);
}
