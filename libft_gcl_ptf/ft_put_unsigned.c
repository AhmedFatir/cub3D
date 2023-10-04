/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:16 by afatir            #+#    #+#             */
/*   Updated: 2023/01/24 07:29:34 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_unsigned(unsigned int n)
{
	int		ln;

	ln = 0;
	if (n >= 0 && n <= 9)
		ln += ft_putchar(n + 48);
	else
	{
		ln += ft_put_unsigned(n / 10);
		ln += ft_put_unsigned(n % 10);
	}
	return (ln);
}
