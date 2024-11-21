/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:57:10 by brendon           #+#    #+#             */
/*   Updated: 2024/11/21 18:46:40 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	{
		printf("Error\n");
		exit(0);
	}
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
	find_exit(data);
	free(line);
	map_size(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_map(&data, argv[1]);
	data.colectible = 0;
	if (verificate_char(&data) && quantity_things(&data)
		&& verify_wall(&data) && verify_mapsize(&data) && verify_path(&data))
	{
		open_window(&data);
		printf("Mapa valido\n");
	}
	else
	{
		printf("Mapa invalido\n");
	}
	free_map(data.map);
}
