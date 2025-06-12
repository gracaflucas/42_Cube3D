/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:55:12 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:30:03 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Initializes substructures within the game data.
 * This function sets default values for the `minimap` and `ray` 
 * substructures inside the main `t_data` structure.
 * @param game Pointer to the game state structure.*/
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
	game->ray.pd = 0;
	game->ray.sx = 0;
	game->ray.sy = 0;
	game->ray.x = 0;
	game->ray.y = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.pixel_x = 0;
	game->ray.pixel_y = 0;
}

/** @brief Initializes the main game data structure.
 * This function sets initial values for the main `t_data` structure used in 
 * the game, including player position, textures, map, and color data. It 
 * also initializes substructures via `init_sub_structs()`.
 * @param game Pointer to the game state structure to initialize.*/
void	init_struct_game(t_data *game)
{
	int	i;

	i = -1;
	if (game == NULL)
		return ;
	game->window = NULL;
	game->init = NULL;
	game->map_array = NULL;
	game->px = 0;
	game->py = 0;
	game->player = 0;
	game->pa = 0;
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

/** @brief Loads and initializes texture images for the game.
 * Uses MiniLibX to load XPM texture files specified in the `textures.files`
 * array, storing the image pointers and related metadata in `textures.images`.
 * On failure, it calls `error_handler()`.
 * @param game Pointer to the initialized game structure.*/
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
		game->textures.images[i].addr = mlx_get_data_addr
			(game->textures.images[i].img,
				&game->textures.images[i].bpp,
				&game->textures.images[i].llen,
				&game->textures.images[i].endian);
	}
}
