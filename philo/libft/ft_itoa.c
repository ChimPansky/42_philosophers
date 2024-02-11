/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:48:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/02 22:20:22 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_int_order(int nb)
{
	size_t	ord;

	ord = 1;
	while (nb / 10 != 0)
	{
		ord++;
		nb /= 10;
	}
	return (ord);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		neg;
	size_t	len;
	long	nb;

	neg = 0;
	nb = (long)n;
	len = ft_get_int_order(n);
	if (nb < 0)
		neg = 1;
	str = ft_calloc(sizeof(char), len + neg + 1);
	if (!str)
		return (NULL);
	if (neg)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[len + neg] = '\0';
	while (len--)
	{
		str[len + neg] = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}
