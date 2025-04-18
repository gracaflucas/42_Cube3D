/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:21:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/16 23:56:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"

# define MOVE_SPEED 0.2
# define ROT_SPEED 0.4

typedef struct s_map
{
	void	*minimap;
	void	*map;
	int		size_line;
	int		y_offset;
	int		x_offset;
	int		pixel_color;
}	t_map;

typedef struct s_data
{
	void		*window;
	void		*init;
	char		**map;
	double			px;
	double			py;
	int			player;
	double		player_angle;
	int			height;
	int			width;
	t_map		minimap;
}	t_data;

int		readmap(char *argv, t_data *game);
int		valid_map(char *str, t_data *game);
void	init_struct_game(t_data *game);

int		close_window(t_data *game);
int		free_map(char **map);
void	render_map(t_data *game);

# endif
