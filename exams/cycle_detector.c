#ifndef LIST_H
# define LIST_H

typedef struct     s_list
{
    int            data;
    struct s_list  *next;
}                  t_list;

#endif

int		cycle_detector(const t_list *list)
{
	const t_list	*hare;
	const t_list	*turtle;

	if (!list)
		return (0);
	hare = list;
	turtle = list;
	while (hare && hare->next)
	{
		hare = hare->next->next;
		turtle = turtle->next;
		if (turtle == hare)
			return (1);
	}
	return (0);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;

	node1 = malloc(sizeof(t_list));
	node2 = malloc(sizeof(t_list));
	node3 = malloc(sizeof(t_list));
	node4 = malloc(sizeof(t_list));

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = (void*)0;

	printf("%d\n", cycle_detector(node1));
}