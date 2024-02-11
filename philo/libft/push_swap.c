/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:14:08 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/25 21:35:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include <stdio.h>	//replace this with ft_printf include...

void	stack_swap(t_stack *stack)
{
	int	temp;

	if (!stack->top || !stack->top->next)
		return ;
	temp = stack->top->val;
	stack->top->val = stack->top->next->val;
	stack->top->next->val = temp;
}

void	stack_transfer_top(t_stack *src, t_stack *dst)
{
	t_snode	*popped;

	popped = stack_pop(src);
	if (popped)
		stack_push_top_node(dst, popped);
}
void	stack_rotate_up(t_stack *stack)
{
	t_snode	*temp;

	if (!stack->top || !stack->top->next)
		return ;
	temp = stack->top->next;
	stack_bottom(stack)->next = stack->top;
	stack->top->next = NULL;
	stack->top = temp;
}
void	stack_rotate_down(t_stack *stack)
{
	t_snode	*temp;
	t_snode	*second_last;

	if (!stack->top || !stack->top->next)
		return ;
	temp = stack->top;
	second_last = stack->top;
	while (second_last->next->next)
		second_last = second_last->next;
	stack->top = second_last->next;
	stack->top->next = temp;
	second_last->next = NULL;
}
void	print_stacks(t_stack stack_a, t_stack stack_b)
{
	t_snode	*snode_a;
	t_snode	*snode_b;

	snode_a = stack_a.top;
	snode_b = stack_b.top;
	while (snode_a || snode_b)
	{
		if (snode_a)
		{
			printf("|%6d", snode_a->val);
			snode_a = snode_a->next;
		}
		else
			printf("|%6s", "");
		printf("|");
		if (snode_b)
		{
			printf("%6d|\n", snode_b->val);
			snode_b = snode_b->next;
		}
		else
			printf("%6s|\n", "");
	}
	printf("---------------\n");
	printf("%4s   |%4s\n", "a", "b");
}
int	main(int ac, char **av)
{
	int	i;
	t_stack	stack_a;
	t_stack	stack_b;

	if (ac < 2)
		return (0);
	i = 1;
	stack_a.top = NULL;
	stack_b.top = NULL;
	while (i < ac)
	{
		if (!ft_str_isnum(av[i]))
		{
			printf("Error\n");
			return (1);
		}

		stack_push_bot_val(&stack_a, ft_atoi(av[i]));
		i++;
	}
	print_stacks(stack_a, stack_b);
	return (0);
}
