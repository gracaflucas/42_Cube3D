/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/11 12:37:47 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void draw_tile(t_data *game, int *img_data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 23)
	{
		x = -1;
		while (++x < 23)
			img_data[(game->minimap.y_offset + y) * (game->minimap.size_line / 4)
				+ (game->minimap.x_offset + x)] = game->minimap.pixel_color;
	}
}

static int	get_color(t_data *game, int i, int j)
{
	int		color;
	char	c;

	c = game->map[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		c = '0';
		game->map[i][j] = '0';
	}
	if (c == '0')
		color = 0x000000;
	else if (c == '1')
		color = 0xFFFFFF;
	return (color);
}

static void	draw_player(t_data *game, int *img_data)
{
	int	player_size;
	int	x;
	int y;
	int draw_x;
	int	draw_y;

	player_size = 10;
	y = (-player_size / 2) - 1;
	while (++y < player_size / 2)
	{
		x = (-player_size / 2) - 1;
		while (++x < player_size / 2)
		{
			draw_x = (int)(game->px * 24) + x;
			draw_y = (int)(game->py * 24) + y;
			if (draw_x >= 0 && draw_x < game->width * 24
				&& draw_y >= 0 && draw_y < game->height * 24)
				img_data[draw_y * (game->minimap.size_line / 4) + draw_x] = 0xFFFF00;
		}
	}
}

void	render_map(t_data *game)
{
	int	*img_data;
	int	i;
	int	j;

	i = -1;
	if (game->minimap.minimap)
		mlx_destroy_image(game->init, game->minimap.minimap);
	game->minimap.minimap = mlx_new_image(game->init, game->width * 24, game->height * 24);
	img_data = (int*)mlx_get_data_addr(game->minimap.minimap, &j, &game->minimap.size_line, &j);
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			game->minimap.pixel_color = get_color(game, i, j);
			game->minimap.x_offset = j * 24;
			game->minimap.y_offset = i * 24;
			draw_tile(game, img_data);
		}
	}
	draw_player(game, img_data);
	mlx_put_image_to_window(game->init, game->window, game->minimap.minimap, 0, 0);
}
