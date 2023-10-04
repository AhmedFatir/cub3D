/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_deci.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:45:14 by afatir            #+#    #+#             */
/*   Updated: 2023/01/24 07:30:46 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_deci(int n)
{
	int		ln;

	ln = 0;
	if (n == -2147483648)
	{
		ln += ft_putstr("-2147483648");
		return (11);
	}
	if (n >= 0 && n <= 9)
		ln += ft_putchar(n + 48);
	else if (n < 0)
	{
		ln += ft_putchar('-');
		ln += ft_put_deci(n * -1);
	}
	else
	{
		ln += ft_put_deci(n / 10);
		ln += ft_put_deci(n % 10);
	}
	return (ln);
}
