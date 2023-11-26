/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:07:56 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/26 18:55:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	*ft_memset(void *s, int c, unsigned int len)
// {
// 	unsigned char	*string;
// 	unsigned int	i;

// 	string = (unsigned char *)s;
// 	i = 0;
// 	while (i < len)
// 	{
// 		string[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (s);
// }

// void	*ft_calloc(unsigned int count, unsigned int size)
// {
// 	char			*tmp;
// 	unsigned int	tsize;

// 	tsize = count * size;
// 	if (count != 0 && size != tsize / count)
// 		return (0);
// 	tmp = (char *)malloc(tsize);
// 	if (!tmp)
// 		return (0);
// 	ft_memset(tmp, 0, tsize);
// 	return (tmp);
// }

// char	*ft_substr(char *s, unsigned int start, unsigned int len)
// {
// 	char			*res;
// 	unsigned int	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start >= (unsigned int)ft_strlen(s))
// 		return ((char *)ft_calloc(1, sizeof(char)));
// 	if ((unsigned int)ft_strlen(s) <= start + len)
// 		res = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
// 	else
// 		res = malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	while (s[start] && i < len)
// 		res[i++] = s[start++];
// 	res[i] = '\0';
// 	return (res);
// }

// char	*ft_strtrim(char *s1, char *set)
// {
// 	unsigned int	i;

// 	if (s1 == NULL || set == NULL)
// 		return (NULL);
// 	while (*s1 && ft_strchr(set, *s1))
// 		s1++;
// 	i = ft_strlen(s1);
// 	while (i && ft_strchr(set, *(s1 + i)))
// 		i--;
// 	return (ft_substr(s1, 0, i + 1));
// }
