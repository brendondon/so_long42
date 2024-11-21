/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:45:03 by brendon           #+#    #+#             */
/*   Updated: 2024/11/21 19:41:47 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>

# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_UP    65362
# define KEY_DOWN  65364
# define KEY_ESC   65307
# define BUFFER_SIZE 10

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*player_img;
	void	*wall_img;
	void	*exit_img;
	void	*colectible_img;
	void	*floor_img;
	char	**map;
	int		mapsize_x;
	int		mapsize_y;
	int		img_width;
	int		img_height;
	int		img_x;
	int		img_y;
	int		win_width;
	int		win_height;
	int		player;
	int		exit;
	int		coletibles_total;
	int		colectible;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_data;

char	*ft_strjoin(char *s1, char *s2);
char	*get_ret(char *str);
int		freefree(char *str);
char	*save_line(char *str);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *str);
int		newline(char *str);
char	*ft_clean(char **s1, char **s2);
char	*ft_strdup(char *s);
int		verificate_char(t_data *data);
int		verify_wall(t_data *data);
int		quantity_things(t_data *data);
void	find_player(t_data *data);
int		verify_exit(char **map, int x, int y);
void	free_map(char **map);
char	**copy_map(char **map);
int		verify_path(t_data *data);
int		verify_mapsize(t_data *data);
void	open_window(t_data *data);
void	map_size(t_data *data);
void	find_exit(t_data *data);
void	close_window(t_data *data);

#endif