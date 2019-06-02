#include "ft_stack.h"

int		ft_check(t_stack *a, t_stack *b)
{
	int		i;
	int		top;

	if (b->top != -1)
		return (0);
	if (a->top == 0)
		return (1);
	top = a->top;
	i = 0;
	while (++i <= top)
		if (a->stack[i - 1] > a->stack[i])
			return (0);
	return (1);
}