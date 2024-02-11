/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:28:59 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/25 20:46:12 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

#include "libft.h"

typedef struct s_stack_node
{
	int	val;
	struct s_stack_node *next;

}			t_snode;

typedef struct s_stack
{
	t_snode	*top;
}			t_stack;

size_t	stack_size(t_stack stack);
int		stack_peek(t_snode snode);
int		stack_push_top_val(t_stack *stack, int val);
int		stack_push_bot_val(t_stack *stack, int val);
int		stack_push_top_node(t_stack *stack, t_snode *snode);
int		stack_push_bot_node(t_stack *stack, t_snode *snode);
t_snode	*stack_pop(t_stack *stack);
t_snode	*stack_bottom(t_stack *stack);

void	stack_print(t_stack stack);

void	print_stacks(t_stack stack_a, t_stack stack_b);

void	stack_swap(t_stack *stack);
void	stack_transfer_top(t_stack *src, t_stack *dst);
void	stack_rotate_up(t_stack *stack);
void	stack_rotate_down(t_stack *stack);



#endif
