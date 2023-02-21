/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:23:23 by begarijo          #+#    #+#             */
/*   Updated: 2023/01/30 16:52:55 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readandsave(int fd, char *save)
{
	char	*buffer;
	int		rb;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	rb = 1;
	while (rb != 0 && !ft_strchr(save, '\n'))
	{
		rb = read(fd, buffer, BUFFER_SIZE);
		if (rb == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[rb] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i])
		line[i++] = '\n';
	return (line);
}

char	*ft_nextline(char *save)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(save) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (save[i])
		next[j++] = save[i++];
	free(save);
	return (next);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
		save = ft_calloc(1, 1);
	save = ft_readandsave(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_nextline (save);
	return (line);
}
