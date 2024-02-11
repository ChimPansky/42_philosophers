/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:29:41 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/25 21:35:39 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include <stdio.h>	// replace this with ft_printf include...

size_t	stack_size(t_stack stack)
{
	size_t	size;
	t_snode	*current;

	if (!stack.top)
		return (0);
	size = 1;
	current = stack.top;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	stack_peek(t_snode snode)
{
	if (!snode.val)
		return (0);
	return (snode.val);
}

int	stack_push_top_node(t_stack *stack, t_snode *snode)
{
	if (!snode)
		return (0);
	snode->next = stack->top;
	stack->top = snode;
	return (1);
}

int	stack_push_top_val(t_stack *stack, int val)
{
	t_snode	*new;

	new = (t_snode *)malloc(sizeof(t_snode *));
	if (!new)
		return (0);
	new->val = val;
	new->next = NULL;
	stack_push_top_node(stack, new);
	return (1);
}
int	stack_push_bot_node(t_stack *stack, t_snode *snode)
{
	if (!snode)
		return (0);
	if (!stack->top)
		stack->top = snode;
	else
		stack_bottom(stack)->next = snode;
	return (1);
}

int	stack_push_bot_val(t_stack *stack, int val)
{
	t_snode	*new;

	new = (t_snode *)malloc(sizeof(t_snode *));
	if (!new)
		return (0);
	new->val = val;
	new->next = NULL;
	stack_push_bot_node(stack, new);
	return (1);
}
t_snode	*stack_pop(t_stack *stack)
{
	t_snode	*popee;

	popee = stack->top;
	if (popee)
	{
		stack->top = popee->next;
		popee->next = NULL;
	}
	return (popee);
}

/* t_snode	**stack_bottom(t_stack *stack)
{
	t_snode **last;

	last = &(stack->top);
	while (*last && (*last)->next)
		last = &(last->next);
	return (last);
} */

t_snode	*stack_bottom(t_stack *stack)
{
	t_snode	*last;

	last = stack->top;
	while (last && last->next)
		last = last->next;
	return (last);
}

void	stack_print(t_stack stack)
{
	t_snode	*current;

	current = stack.top;
	printf("|-------\n");
	if (!current)
		printf("empty\n");
	while (current)
	{
		printf("%7d\n", current->val);
		current = current->next;
	}
	printf("-------|\n");
}
