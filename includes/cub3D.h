/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:21:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/07 13:13:55 by lufiguei         ###   ########.fr       */
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

typedef struct s_data
{
	void		*window;
	void		*init;
	char		**map;
	int			px;
	int			py;
	int			player;
}	t_data;

int		readmap(char *argv, t_data *game);
int		valid_map(char *str, t_data *game);
void	init_struct_game(t_data *game);

int		close_window(t_data *game);
int		free_map(char **map);

# endif
