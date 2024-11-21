/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:06:53 by brendon           #+#    #+#             */
/*   Updated: 2024/11/21 16:23:23 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_size(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
			j++;
		i++;
	}
	data->mapsize_x = j;
	data->mapsize_y = i;
}

void	free_map(char **map)
{
	int	i;
	
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**copy_map(char **map)
{
	char	**new_map;
	int		i;
	
	i = 0;
	while(map[i] != NULL)
		i++;
	new_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_map == NULL)
		return (NULL);
	i = 0;
	while (map[i] != NULL)
	{
		new_map[i] = ft_strdup(map[i]);
		if (new_map[i] == NULL)
		{
			free_map(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}
void	find_player(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'P')
			{
				data->player_x = i;
				data->player_y = j;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}
void	find_exit(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'E')
			{
				data->exit_x = i;
				data->exit_y = j;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}