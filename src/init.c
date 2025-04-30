/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:55:12 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/30 11:00:48 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_sub_structs(t_data *game)
{
	game->minimap.map = NULL;
	game->minimap.minimap = NULL;
	game->minimap.pixel_color = 0;
	game->minimap.size_line = 0;
	game->minimap.x_offset = 0;
	game->minimap.y_offset = 0;
	game->minimap.wall_color = 0;
	game->ray.angle = 0;
	game->ray.hit = 2;
	game->ray.perp_dist = 0;
	game->ray.side_dist_x = 0;
	game->ray.side_dist_y = 0;
	game->ray.x = 0;
	game->ray.y = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.pixel_x = 0;
	game->ray.pixel_y = 0;
}

void	init_struct_game(t_data *game)
{
	int	i;

	i = -1;
	if (game == NULL)
		return ;
	game->window = NULL;
	game->init = NULL;
	game->map = NULL;
	game->px = 0;
	game->py = 0;
	game->player = 0;
	game->player_angle = 0;
	game->height = 0;
	game->width = 0;
	while (++i < 4)
		game->textures.files[i] = NULL;
	i = -1;
	while (++i < 5)
		game->textures.images[i].img = NULL;
	game->colors.c_hex = 0;
	game->colors.ceiling = NULL;
	game->colors.f_hex = 0;
	game->colors.floor = NULL;
	init_sub_structs(game);
}

void	init_images(t_data *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->textures.images[i].img = mlx_xpm_file_to_image(game->init,
			game->textures.files[i], &game->textures.images[i].width,
			&game->textures.images[i].height);
		if (!game->textures.images[i].img)
			error_handler(game, "Error\nFailed to load textures.");
		game->textures.images[i].addr = mlx_get_data_addr(game->textures.images[i].img,
			&game->textures.images[i].bits_per_pixel, &game->textures.images[i].line_len,
			&game->textures.images[i].endian);
	}
}
