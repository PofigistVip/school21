#ifndef FT_STACK_H
# define FT_STACK_H

typedef struct	s_stack
{
	int		size;
	int		top;
	int		*stack;
}				t_stack;

/*
** ft_get_args.c
*/

int				ft_get_args(int argc, char **argv, t_stack **a, t_stack **b);
int				ft_free_stacks(t_stack **a, t_stack **b);

/*
** ft_stack.c
*/

t_stack			*ft_stack_new(int size);
void			ft_stack_free(t_stack **stk);
int				ft_stack_contains(t_stack *stk, int numb);
void			ft_stack_push(t_stack *stk, int numb);
int				ft_stack_pop(t_stack *stk);

/*
** ft_do_commands.c 
*/

int				ft_do_commands(t_stack *a, t_stack *b);

/*
** ft_check.c
*/

int		ft_check(t_stack *a, t_stack *b);
#endif