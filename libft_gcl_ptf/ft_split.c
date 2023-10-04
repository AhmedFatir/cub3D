/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:01:42 by afatir            #+#    #+#             */
/*   Updated: 2023/02/05 15:21:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count(const char s, const char c)
{
	if (s == c)
		return (1);
	return (0);
}

static	char	*ft_sep(char const *s1, char const set)
{
	size_t	i;
	size_t	ls;
	size_t	end;

	if (!s1)
		return (0);
	i = 0;
	ls = ft_strlen(s1) - 1;
	while (*s1 && (ft_count(set, s1[i])))
		i++;
	while (ls && *s1 && (ft_count(set, s1[ls])))
		ls--;
	end = (ls - i) + 1;
	return (ft_substr(s1, i, end));
}

static int	ft_wcount(const char *s, char c)
{
	int	i;
	int	ls;

	if (!s)
		return (0);
	i = 0;
	ls = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			ls++;
			while (s[i] && s[i] == c)
				i++;
			i--;
		}
		i++;
	}
	return (ls);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**p;
	int		i;
	int		start;
	int		end;

	str = ft_sep(s, c);
	p = ft_calloc((ft_wcount(str, c) + 1), sizeof(char *));
	if (!s || !p)
		return (free(p), NULL);
	i = -1;
	start = 0;
	end = 0;
	while (str[++i] && i < ft_wcount(str, c))
	{
		while (str[end] && str[end] != c)
			end++;
		p[i] = ft_substr(str, start, end - start);
		if (!p)
			return (ft_free_all(p));
		while (str[end] == c)
			end++;
		start = end;
	}
	return (free(str), p);
}
