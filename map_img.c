/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:37:03 by brendon           #+#    #+#             */
/*   Updated: 2024/11/21 18:03:06 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_img(t_data *data)
{
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "img/wall.xpm",
			&data->img_width, &data->img_height);
	if (!data->wall_img)
	{
		printf("Error loading wall image\n");
		exit(1);
	}
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "img/ground.xpm",
			&data->img_width, &data->img_height);
	if (!data->floor_img)
	{
		printf("Error loading floor image\n");
		exit(1);
	}
	data->player_img = mlx_xpm_file_to_image(data->mlx, "img/player.xpm",
			&data->img_width, &data->img_height);
	if (!data->player_img)
	{
		printf("Error loading player image\n");
		exit(1);
	}
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "img/exit.xpm",
			&data->img_width, &data->img_height);
	if (!data->exit_img)
	{
		printf("Error loading exit image\n");
		exit(1);
	}
	data->colectible_img = mlx_xpm_file_to_image(data->mlx, "img/c1.xpm",
			&data->img_width, &data->img_height);
	if (!data->colectible_img)
	{
		printf("Error loading collectible image\n");
		exit(1);
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->mapsize_y)
	{
		y = 0;
		while (y < data->mapsize_x)
		{
			if (data->map[x][y] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall_img, y * data->img_width, x * data->img_height);
			else if (data->map[x][y] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->floor_img, y * data->img_width, x * data->img_height);
			else if (data->map[x][y] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player_img, y * data->img_width, x * data->img_height);
			else if (data->map[x][y] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit_img, y * data->img_width, x * data->img_height);
			else if (data->map[x][y] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->colectible_img, y * data->img_width, x * data->img_height);
			y++;
		}
		x++;
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
	{
		new_x = data->player_x;
		new_y = data->player_y;
		return ;
	}
	else if (data->map[new_x][new_y] == 'E')
	{
		if (data->colectible == 0)
		{
			printf("You WIN\n");
			mlx_destroy_window(data->mlx, data->win);
			exit(0);
		}
		data->map[data->player_x][data->player_y] = '0';
		data->map[new_x][new_y] = 'P';
		data->player_x = new_x;
		data->player_y = new_y;
	}
	else if (data->map[new_x][new_y] == 'C')
	{
		data->colectible--;
		data->map[data->player_x][data->player_y] = '0';
		data->map[new_x][new_y] = 'P';
		data->player_x = new_x;
		data->player_y = new_y;
	}
	else if (data->map[new_x][new_y] == '0')
	{
		data->map[data->player_x][data->player_y] = '0';
		data->map[new_x][new_y] = 'P';
		data->player_x = new_x;
		data->player_y = new_y;
	}
	if (new_x != data->exit_x || new_y != data->exit_y)
		data->map[data->exit_x][data->exit_y] = 'E' ;
	else
		return ;
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
		mlx_destroy_window(data->mlx, data->win);
		printf("Exit program\n");
		exit(0);
	}
	what_isit(data, new_x, new_y);
	put_image_to_window(data);
	return (0);
}

void	open_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win_width = data->mapsize_x * 40;
	data->win_height = data->mapsize_y * 40;
	data->win = mlx_new_window(data->mlx,
			data->win_width, data->win_height, "Move Image");
	load_img(data);
	put_image_to_window(data);
	mlx_key_hook(data->win, key_press, data);
	mlx_loop(data->mlx);
}
