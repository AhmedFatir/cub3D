/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:32:31 by afatir            #+#    #+#             */
/*   Updated: 2022/10/30 23:23:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (dst > src)
		while (i--)
			*((char *)dst + i) = *((char *)src + i);
	else
		return (ft_memcpy(dst, src, n));
	return (dst);
}
