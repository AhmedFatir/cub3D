/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:34:42 by afatir            #+#    #+#             */
/*   Updated: 2023/01/28 00:43:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_save(char *save)
{
	int		j;
	int		i;
	char	*p;

	j = 0;
	i = 0;
	while (save[j] && save[j] != '\n')
		j++;
	if (!save[j])
		return (free(save), NULL);
	p = malloc ((ft_strlen(save) - j) * sizeof(char));
	if (!p)
		return (free(save), NULL);
	while (save[j])
	{
		p[i] = save[j + 1];
		j++;
		i++;
	}
	return (free(save), p);
}

char	*ft_get(char *save)
{
	int		i;
	char	*p;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	p = malloc (sizeof(char) * (i + 2));
	if (!p)
		return (0);
	p[i + 1] = '\0';
	while (i >= 0)
	{
		p[i] = save[i];
		i--;
	}
	return (p);
}

char	*ft_read(int fd, char *save)
{
	int		read_bytes;
	char	*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	read_bytes = 1;
	while (read_bytes && ft_checkc(save, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == 0 && *save)
			break ;
		else if (read_bytes <= 0)
			return (free(buff), free(save), NULL);
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	return (free(buff), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!save)
		save = ft_strdup("");
	save = ft_read(fd, save);
	if (!save)
		return (0);
	line = ft_get(save);
	save = ft_save(save);
	return (line);
}
