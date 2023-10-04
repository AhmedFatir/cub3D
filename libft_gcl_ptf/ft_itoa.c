/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:38:35 by afatir            #+#    #+#             */
/*   Updated: 2023/01/19 00:35:14 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count(int n)
{
	size_t		ls;

	ls = 0;
	if (n <= 0)
		ls++;
	while (n)
	{
		n /= 10;
		ls++;
	}
	return (ls);
}

char	*ft_itoa(int n)
{
	char		*ps;
	long int	nb;
	size_t		ls;

	nb = n;
	ls = ft_count(n);
	ps = ft_calloc(sizeof(char), (ls + 1));
	if (!ps)
		return (NULL);
	if (!nb)
		ps[0] = '0';
	if (nb < 0)
	{
		ps[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		ps[ls - 1] = nb % 10 + 48;
		nb = nb / 10;
		ls--;
	}
	return (ps);
}
