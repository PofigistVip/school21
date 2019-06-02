#include "libft.h"
#include "get_next_line.h"
#include "ft_stack.h"

void		ft_comm_swap(t_stack *stk, t_stack *stk2)
{
	int		top;
	int		buff;

	top = stk->top;
	if (top <= 1)
		return ;
	buff = stk->stack[top];
	stk->stack[top] = stk->stack[top - 1];
	stk->stack[top - 1] = buff;
	if (stk2)
	{
		top = stk2->top;
		if (top <= 1)
			return ;
		buff = stk2->stack[top];
		stk2->stack[top] = stk2->stack[top - 1];
		stk2->stack[top - 1] = buff;
	}
}

void		ft_comm_push(t_stack *from, t_stack *to)
{
	if (from->top != -1)
		ft_stack_push(to, ft_stack_pop(from));
}

void		ft_comm_rotate(t_stack *stk, t_stack *stk2)
{
	int		temp;

	temp = stk->stack[stk->top];
	ft_memmove(stk->stack + 1, stk->stack, sizeof(int) * (stk->top - 1));
	stk->stack[0] = temp;
	if (stk2)
	{
		temp = stk2->stack[stk2->top];
		ft_memmove(stk2->stack + 1, stk2->stack, sizeof(int) * (stk2->top - 1));
		stk2->stack[0] = temp;
	}
}

void		ft_comm_reverse_rotate(t_stack *stk, t_stack *stk2)
{
	int		temp;

	temp = stk->stack[0];
	ft_memmove(stk->stack, stk->stack + 1, sizeof(int) * (stk->top - 1));
	stk->stack[stk->top] = temp;
	if (stk2)
	{
		temp = stk2->stack[0];
		ft_memmove(stk2->stack, stk2->stack + 1, sizeof(int) * (stk2->top - 1));
		stk2->stack[stk2->top] = temp;
	}
}

int		ft_do_commands(t_stack *a, t_stack *b)
{
	char	*str;

	str = 0;
	while (get_next_line(0, &str))
	{
		if (ft_strcmp("sa", str) == 0)
			ft_comm_swap(a, 0);
		else if (ft_strcmp("sb", str) == 0)
			ft_comm_swap(b, 0);
		else if (ft_strcmp("ss", str) == 0)
			ft_comm_swap(a, b);
		else if (ft_strcmp("pa", str) == 0)
			ft_comm_push(b, a);
		else if (ft_strcmp("pb", str) == 0)
			ft_comm_push(a, b);
		else if (ft_strcmp("ra", str) == 0)
			ft_comm_rotate(a, 0);
		else if (ft_strcmp("rb", str) == 0)
			ft_comm_rotate(b, 0);
		else if (ft_strcmp("rr", str) == 0)
			ft_comm_rotate(a, b);
		else if (ft_strcmp("rra", str) == 0)
			ft_comm_reverse_rotate(a, 0);
		else if (ft_strcmp("rrb", str) == 0)
			ft_comm_reverse_rotate(b, 0);
		else if (ft_strcmp("rrr", str) == 0)
			ft_comm_reverse_rotate(a, b);
		else
			return (0);
	}
	return (1);
}