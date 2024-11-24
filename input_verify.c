/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:43:45 by brendon           #+#    #+#             */
/*   Updated: 2024/11/22 08:57:25 by brendon          ###   ########.fr       */
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
