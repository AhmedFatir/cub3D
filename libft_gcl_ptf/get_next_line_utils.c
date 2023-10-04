/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:35:05 by afatir            #+#    #+#             */
/*   Updated: 2023/02/02 19:59:59 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_checkc(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		str1;
	size_t		str2;
	char		*p;

	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (str1 + str2) + 1);
	if (!p)
		return (0);
	ft_memcpy(p, s1, str1);
	ft_memcpy((p + str1), s2, str2);
	p[str1 + str2] = '\0';
	free(s1);
	return (p);
}
