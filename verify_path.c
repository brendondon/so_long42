/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:56:31 by brendon           #+#    #+#             */
/*   Updated: 2024/11/22 09:16:49 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

	map = copy_map(data->map);
	if (map == NULL)
		return (0);
	find_player(data);
	if (verify_exit(map, data->player_x, data->player_y) && verify_cpath(data))
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}

int	verify_cpath(t_data *data)
{
	char	**map;

	map = copy_map(data->map);
	if (map == NULL)
		return (0);
	find_player(data);
	verify_collect(map, data->player_x, data->player_y, data);
	if (data->coletibles_total != data->colectible)
	{
		free_map(map);
		return (0);
	}
	free_map(map);
	return (1);
}
