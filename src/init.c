/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:55:12 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/21 00:53:04 by marvin           ###   ########.fr       */
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
	game->ray.angle = 0;
	game->ray.hit = 2;
	game->ray.perp_dist = 0;
	game->ray.ray_dist = 0;
	game->ray.x = 0;
	game->ray.y = 0;
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

static void	destroy_images(t_data *game)
{
	if (game->minimap.minimap)
		mlx_destroy_image(game->init, game->minimap.minimap);
	if (game->minimap.map)
		mlx_destroy_image(game->init, game->minimap.map);
	game->minimap.minimap = NULL;
	game->minimap.map = NULL;
}

int	close_window(t_data *game)
{
	destroy_images(game);
	mlx_destroy_window(game->init, game->window);
	mlx_destroy_display(game->init);
	free_map(game->map);
	free(game->init);
	game->init = NULL;
	exit(0);
}
