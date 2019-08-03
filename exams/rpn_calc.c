#include <stdio.h>
#include <stdlib.h>

int		is_op(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int		is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int		is_space(char c)
{
	return (c == ' ');
}

int		validation(char *str)
{
	int		number_counter;
	int		op_counter;


	number_counter = 0;
	op_counter = 0;
	while (*str)
	{
		if (is_op(*str))
		{
			if (number_counter && (*(str - 1) && !is_space(*(str - 1))))
				return (0);
			if ((*str != '+' && *str != '-') || (!is_digit(*(str + 1))))
				++op_counter;
		}
		else if (is_digit(*str))
		{
			if (number_counter == 0 || (*(str - 1) && !is_digit(*(str - 1))))
				++number_counter;
		}
		else if (!is_space(*str))
			return (0);
		++str;
	}
	return (number_counter - op_counter == 1 ? 1 : 0);
}

typedef struct	s_stack
{
	int				num;
	struct s_stack	*next;
}				t_stack;

int		pop(t_stack **stack)
{
	int		num;
	t_stack	*temp;

	if (!stack || !*stack)
		return (0);
	num = (*stack)->num;
	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
	return (num);
}

void	push(t_stack **stack, int num)
{
	t_stack	*elem;

	if (!stack)
		return ;
	elem = (t_stack*)malloc(sizeof(t_stack));
	if (!elem)
		return ;
	elem->num = num;
	elem->next = *stack;
	*stack = elem;
}

int		do_op(int num1, int num2, char op)
{
	if (op == '+')
		return (num1 + num2);
	if (op == '-')
		return (num1 - num2);
	if (op == '*')
		return (num1 * num2);
	if (op == '/')
		return (num1 / num2);
	if (op == '%')
		return (num1 % num2);
	return (0);
}

int		calc(char *str)
{
	t_stack	*stack;
	int		num1;
	int		num2;

	stack = (void*)0;
	while (*str)
	{
		if (!is_space(*str))
		{
			if (is_digit(*str))
			{
				push(&stack, atoi(str));
				while (*str && is_digit(*str))
					++str;
			}
			else if (is_op(*str))
			{
				if ((*str == '+' || *str == '-') && is_digit(*(str + 1)))
				{
					push(&stack, atoi(str));
					++str;
					while (*str && is_digit(*str))
						++str;
				}
				else
				{
					num2 = pop(&stack);
					num1 = pop(&stack);
					if (num2 == 0 && (*str == '/' || *str == '%'))
					{
						printf("Error\n");
						return (-2);
					}
					push(&stack, do_op(num1, num2, *str));
				}
			}
		}
		++str;
	}
	printf("%d\n", pop(&stack));
	return (0);
}

int		main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	if (argc != 2 || validation(argv[1]) == 0)
	{
		printf("Error\n");
		return (-1);
	}
	return (calc(argv[1]));
}