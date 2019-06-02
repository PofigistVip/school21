#include "ft_stack.h"
#include <string.h>
#include <stdlib.h>

t_stack		*ft_stack_new(int size)
{
	t_stack		*stk;

	if ((stk = (t_stack*)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	if ((stk->stack = (int*)malloc(sizeof(int) * size)) == NULL)
	{
		free(stk);
		return (NULL);
	}
	stk->size = size;
	stk->top = -1;
	return (stk);
}

void		ft_stack_free(t_stack **stk)
{
	if (stk != NULL && *stk != NULL)
	{
		free((*stk)->stack);
		free(*stk);
		*stk = 0;
	}
}

int			ft_stack_contains(t_stack *stk, int numb)
{
	int		i;
	int		top;
	int		*stack;

	if (stk == NULL)
		return (0);
	top = stk->top;
	if (top == -1)
		return (0);
	stack = stk->stack;
	i = -1;
	while (++i < top)
	{
		if (*stack == numb)
			return (1);
		++stack;
	}
	return (0);
}

void		ft_stack_push(t_stack *stk, int numb)
{
	if (stk == NULL)
		return ;
	++(stk->top);
	stk->stack[stk->top] = numb;
}

int			ft_stack_pop(t_stack *stk)
{
	int		numb;

	if (stk == NULL || stk->top == -1)
		return (0);
	numb = stk->stack[stk->top];
	--(stk->top);
	return (numb);	
}