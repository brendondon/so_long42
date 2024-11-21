/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:43:45 by brendon           #+#    #+#             */
/*   Updated: 2024/11/21 19:48:02 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verify_mapsize(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
			j++;
		if (j != data->mapsize_x)
			return (0);
		if ((data->map[i + 1] == NULL ) && (data->map[i][j] == '\n'))
			return (0);
		j = 0;
		i++;
	}
	if (data->mapsize_x == data->mapsize_y)
		return (0);
	return (1);
}

//vefica caracteres validos
int	verificate_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
					&& data->map[i][j] != 'P' && data->map[i][j] != 'E'
					&& data->map[i][j] != 'C')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

//verifica se o mapa tem todas as paredes
int	verify_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[0][j] != '1' || data->map[i][0] != '1')
				return (0);
			if ((data->map[i][j + 1] == '\0' && data->map[i][j] != '1')
					|| (data->map[i + 1] == NULL && data->map[i][j] != '1'))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

//verifica se o mapa tem a quantidade correta de coisas
int	quantity_things(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->player = 0;
	data->exit = 0;
	data->coletibles_total = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'P')
				data->player++;
			if (data->map[i][j] == 'E')
				data->exit++;
			if (data->map[i][j] == 'C')
				data->coletibles_total++;
			j++;
		}
		i++;
	}
	if (data->player != 1 || data->exit != 1 || data->coletibles_total < 1)
		return (0);
	return (1);
}

int	verify_exit(char **map, int x, int y)
{
	if (map[x][y] == 'E')
		return (1);
	if (map[x][y] == '1' || map[x][y] == 'x')
		return (0);
	if (map[x][y] == '0' || map[x][y] == 'C' || map[x][y] == 'P')
		map[x][y] = 'x';
	return (verify_exit(map, x + 1, y) || verify_exit(map, x, y - 1)
		|| verify_exit(map, x - 1, y) || verify_exit(map, x, y + 1));
}

void	verify_collect(char **map, int x, int y, t_data *data)
{
	if (map[x][y] == 'C')
	{
		data->colectible++;
		map[x][y] = 'x';
	}
	else if (map[x][y] == '1' || map[x][y] == 'x')
		return ;
	else if (map[x][y] == '0' || map[x][y] == 'P' || map[x][y] == 'E')
		map[x][y] = 'x';
	verify_collect(map, x + 1, y, data);
	verify_collect(map, x - 1, y, data);
	verify_collect(map, x, y + 1, data);
	verify_collect(map, x, y - 1, data);
	return ;
}

int	verify_path(t_data *data)
{
	char	**map;
	char	**map_c;
	int		test;

	test = 0;
	map = copy_map(data->map);
	if (map == NULL)
		return (0);
	map_c = copy_map(data->map);
	if (map_c == NULL)
	{
		free_map(map_c);
		return (0);
	}
	find_player(data);
	verify_collect(map_c, data->player_x, data->player_y, data);
	if (data->coletibles_total != data->colectible)
	{
		free_map(map);
		free_map(map_c);
		return (0);
	}
	if (verify_exit(map, data->player_x, data->player_y))
	{
		free_map(map);
		free_map(map_c);
		return (1);
	}
	free_map(map);
	free_map(map_c);
	return (0);
}
