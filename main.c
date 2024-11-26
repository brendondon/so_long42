/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:57:10 by brendon           #+#    #+#             */
/*   Updated: 2024/11/26 19:44:16 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]))
		i ++;
	if (n == i)
		return (0);
	else
		return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
}

size_t	size_mtz(char *argv)
{
	int		fd;
	char	*line;
	size_t	i;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i + 1);
}

void	init_map(t_data *data, char *argv)
{
	int		fd;
	char	*line;
	int		i;

	data->map = (char **)malloc(sizeof(char *) * size_mtz(argv));
	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_exit("Error\n", 1);
	if (ft_strncmp(argv + ft_strlen(argv) - 4,
			".ber", ft_strlen(argv) - 4) != 0)
		ft_exit("Error\n", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->map[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->map[i] = NULL;
	close(fd);
	free(line);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_map(&data, argv[1]);
	find_exit(&data);
	map_size(&data);
	data.colectible = 0;
	if (verificate_char(&data) && quantity_things(&data)
		&& verify_wall(&data) && verify_mapsize(&data) && verify_path(&data))
		open_window(&data);
	else
	{
		free_map(data.map);
		ft_exit("Mapa invalido\n", 1);
	}
	free_map(data.map);
}
