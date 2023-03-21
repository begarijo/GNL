/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:30:30 by begarijo          #+#    #+#             */
/*   Updated: 2023/03/21 16:30:43 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*At this point, the line is already returned, the buffer has all the info,
* including the line, so it's going to be updated.
*
* Again, it looks for the \n, and in this point, copies the remain in a str.
* Frees the buffer, and return the new line that have to work with.*/

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

/*It looks for the \n in the buffer, and then allocate enought memory in a str
* to copy only until the \n.
*
* Manually, the \n is also copied.*/

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i])
		line[i++] = '\n';
	return (line);
}

/*It allocate enought memory in a str to save what the function 'read' reads.
 *
 * The bytes readed (br) can't be 0, and it initialice in 1 because always, at least
 * the \0 character is going to be there. Also, there can't be any \n in our str,
 * as we need to return only a line.
 *
 * As the function read returns the amount of bytes readed, this value is assigned
 * to br, and in case of error (-1), it's necessary to free all the str's that can
 * have anything in there.
 *
 * In case everything is ok, the end of the str is going to be \0, and the static
 * (buffer) and the new str are joined to save all the info.
 *
 * The str is no more needed, so it's free and returned the new buffer.*/

char	*ft_readfile(int fd, char *buffer)
{
	char	*res;
	int		br;

	res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	br = 1;
	while (br != 0 && !ft_strchr(res, '\n'))
	{
		br = read(fd, res, BUFFER_SIZE);
		if (br == -1)
		{
			free(res);
			free(buffer);
			return (NULL);
		}
		res[br] = '\0';
		buffer = ft_strjoin(buffer, res);
	}
	free(res);
	return (buffer);
}

/*This is the principal function, and it checks if there's any error with fd or the buffer size.
 *
 * For the first call to our function, it's necessary to create our static by allocating
 * memory in it. Once it exists, and there's no errors, the buffer is going to have
 * the value the function readfile returns. This value is the result of reading the fd.
 *
 * Then, with the buffer updated, the line is going to have the value the function line
 * returns, which is the result of looking for the \n in the buffer updated.
 *
 * And in the end, the buffer is going to be updated again, with the remain lines
 * and data that the ft_line remains after returning the first line.*/

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, 1);
	buffer[fd] = ft_readfile(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}
