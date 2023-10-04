/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:49:30 by afatir            #+#    #+#             */
/*   Updated: 2022/10/30 05:17:14 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		slen;
	char		*b;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		slen = ft_strlen(s) + 1;
	else
		slen = len + 1;
	b = ft_calloc(slen, sizeof(char));
	if (!b)
		return (0);
	if (start >= ft_strlen(s))
		return (b);
	while (i < len && s[start + i])
	{
		b[i] = s[start + i];
		i++;
	}
	return (b);
}
