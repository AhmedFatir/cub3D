/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:11:08 by afatir            #+#    #+#             */
/*   Updated: 2023/01/24 07:29:48 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_ad(unsigned long p, char *s)
{
	int		ln;

	ln = 0;
	if (p >= 16)
		ln += ft_put_ad(p / 16, s);
	if (p > 9)
		ln += ft_putchar(s[p % 16]);
	if (p < 10)
		ln += ft_putchar(p + 48);
	return (ln);
}
