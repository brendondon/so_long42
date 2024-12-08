/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:04:11 by brendon           #+#    #+#             */
/*   Updated: 2024/12/08 18:09:04 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	ft_exit(char *str, int i)
{
	if (i == 1)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(str, 1);
	exit(i);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->player_img);
	mlx_destroy_image(data->mlx, data->wall_img);
	mlx_destroy_image(data->mlx, data->exit_img);
	mlx_destroy_image(data->mlx, data->colectible_img);
	mlx_destroy_image(data->mlx, data->floor_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map);
	exit(0);
}

void	open_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win_width = data->mapsize_x * 40;
	data->win_height = data->mapsize_y * 40;
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "So_long");
	load_img(data);
	put_image_to_window(data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_press, data);
	mlx_loop(data->mlx);
}

void	ft_move(t_data *data, int new_x, int new_y)
{
	ft_putnbr(data->step++);
	write(1, "\n", 1);
	data->map[data->player_x][data->player_y] = '0';
	data->map[new_x][new_y] = 'P';
	data->player_x = new_x;
	data->player_y = new_y;
}
