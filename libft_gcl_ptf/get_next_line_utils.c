/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:35:05 by afatir            #+#    #+#             */
/*   Updated: 2023/07/11 01:34:30 by souledla         ###   ########.fr       */
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
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	return (free(s1), s1 = NULL, p);
}

char	*ft_strjoin_p(char *s1, char s2)
{
	size_t		n;
	int			i;
	char		*p;

	n = ft_strlen(s1);
	i = ft_strlen(s1);
	p = malloc(sizeof(char) * n + 2);
	if (!p)
		return (0);
	p[n + 1] = '\0';
	p[n] = s2;
	while (i--)
		p[i] = s1[i];
	free(s1);
	return (p);
}
