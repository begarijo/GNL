/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:20:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/01/13 12:37:57 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *save, char const *buffer)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	len = (int) ft_strlen(save) + (int) ft_strlen(buffer);
	new = malloc(sizeof (char) * len + 1);
	if (!new)
		return (NULL);
	while (save[i] != '\0')
	{
		new[i] = save[i];
		i++;
	}
	j = 0;
	while (buffer[j] != '\0')
	{
		new[i + j] = buffer[j];
		j++;
	}
	new[i + j] = '\0';
	free(save);
	return (new);
}

char	*ft_strchr(const char *save, int c)
{
	int		i;
	char	*s;

	i = 0;
	if (!save)
		return (NULL);
	s = (char *)save;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return (&s[i]);
	else
		return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;

	new = malloc(count * size);
	if (!new)
		return (NULL);
	ft_bzero(new, size * count);
	return (new);
}
