/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:59:32 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/21 16:04:18 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	i = 0;
	j = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
		temp[i++] = s2[j++];
	free(s1);
	s1 = NULL;
	return (temp);
}

char	*get_ret(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 1);
	if (!line)
	{
		free (str);
		return (NULL);
	}
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	return (line);
}

int	freefree(char *str)
{
	free (str);
	return (1);
}

char	*save_line(char *str)
{
	char		*new_line;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!*str && freefree(str))
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] && freefree(str))
		return (NULL);
	new_line = ft_calloc(sizeof(char), ft_strlen(str) - i + 1);
	while (str[++i])
		new_line[j++] = str[i];
	free(str);
	if (*new_line == 0 && freefree(new_line))
		return (NULL);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*dest;
	char		*buf;
	char		*line;
	int			char_read;

	char_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (!(newline(buf)) && char_read)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
			return (ft_clean(&dest, &buf));
		buf[char_read] = '\0';
		dest = ft_strjoin(dest, buf);
	}
	line = get_ret(dest);
	dest = save_line(dest);
	free(buf);
	buf = NULL;
	return (line);
}