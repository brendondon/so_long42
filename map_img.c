/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:37:03 by brendon           #+#    #+#             */
/*   Updated: 2024/12/08 18:06:47 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_img(t_data *data)
{
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "img/wall.xpm",
			&data->img_width, &data->img_height);
	if (!data->wall_img)
		ft_exit("Error\nloading wall image\n", 1);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "img/ground.xpm",
			&data->img_width, &data->img_height);
	if (!data->floor_img)
		ft_exit("Error\nloading floor image\n", 1);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "img/player.xpm",
			&data->img_width, &data->img_height);
	if (!data->player_img)
		ft_exit("Error\nloading player image\n", 1);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "img/exit.xpm",
			&data->img_width, &data->img_height);
	if (!data->exit_img)
		ft_exit("Error\nloading exit image\n", 1);
	data->colectible_img = mlx_xpm_file_to_image(data->mlx, "img/c1.xpm",
			&data->img_width, &data->img_height);
	if (!data->colectible_img)
		ft_exit("Error\nloading colectible image\n", 1);
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	void	*img;

	x = -1;
	while (++x < data->mapsize_y)
	{
		y = -1;
		while (++y < data->mapsize_x)
		{
			if (data->map[x][y] == '1')
				img = data->wall_img;
			else if (data->map[x][y] == '0')
				img = data->floor_img;
			else if (data->map[x][y] == 'P')
				img = data->player_img;
			else if (data->map[x][y] == 'E')
				img = data->exit_img;
			else if (data->map[x][y] == 'C')
				img = data->colectible_img;
			if (img)
				mlx_put_image_to_window(data->mlx, data->win, img,
					y * data->img_width, x * data->img_height);
		}
	}
}

void	put_image_to_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
}

void	what_isit(t_data *data, int new_x, int new_y)
{
	if (data->map[new_x][new_y] == '1')
		return ;
	if (data->map[new_x][new_y] == 'E')
	{
		if (data->colectible == 0)
		{
			ft_putstr_fd("You win!\n", 1);
			close_window(data);
		}
		ft_move(data, new_x, new_y);
	}
	else if (data->map[new_x][new_y] == 'C')
	{
		data->colectible--;
		ft_move(data, new_x, new_y);
	}
	else if (data->map[new_x][new_y] == '0')
		ft_move(data, new_x, new_y);
	if (new_x != data->exit_x || new_y != data->exit_y)
		data->map[data->exit_x][data->exit_y] = 'E';
}

int	key_press(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == KEY_LEFT)
		new_y -= 1;
	if (keycode == KEY_RIGHT)
		new_y += 1;
	if (keycode == KEY_UP)
		new_x -= 1;
	if (keycode == KEY_DOWN)
		new_x += 1;
	if (keycode == KEY_ESC)
	{
		close_window(data);
		exit(0);
	}
	what_isit(data, new_x, new_y);
	put_image_to_window(data);
	return (0);
}
