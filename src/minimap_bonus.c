/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <lufiguei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:02:31 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/13 17:02:31 by lufiguei         ###   ########.fr       */
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

static int	get_color(char c)
{
	int	color;

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		color = 0xFFFF00;
	else if (c == '0')
		color = 0x000000;
	else if (c == '1')
		color = 0xFFFFFF;
	return (color);
}

// how to fix the size of player in comparison with the whole map?
// how to walk in the map only slighly, not the whole block?
void	render_map(t_data *game)
{
	int	*img_data;
	int	i;
	int	j;

	i = -1;
	if (!game->minimap.minimap)
		game->minimap.minimap = mlx_new_image(game->init, game->width * 24, game->height * 24);
	img_data = (int*)mlx_get_data_addr(game->minimap.minimap, &j, &game->minimap.size_line, &j);
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			game->minimap.pixel_color = get_color(game->map[i][j]);
			game->minimap.x_offset = j * 24;
			game->minimap.y_offset = i * 24;
			draw_tile(game, img_data);
		}
	}
	mlx_put_image_to_window(game->init, game->window, game->minimap.minimap, 0, 0);
}
