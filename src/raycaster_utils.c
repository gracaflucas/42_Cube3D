/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:54 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:32:10 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Calculates the correct texture X coordinate for wall rendering,
 * taking into account the ray hit direction and flipping texture accordingly.
 * Uses the player's position and ray distance to find the exact wall hit point,
 * then calculates the texture coordinate along the wall.
 * @param texture Pointer to the texture image struct containing width info.
 * @param game Pointer to the game data struct containing ray info.
 * @return The X coordinate in the texture to sample from.*/
int	flip_textures(t_image *texture, t_data *game)
{
	int		tex_x;
	double	wall_x;

	if (game->ray.hit == 0)
		wall_x = game->py + game->ray.pd * game->ray.y;
	else
		wall_x = game->px + game->ray.pd * game->ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (game->ray.hit == 0)
	{
		if (game->ray.x < 0)
			tex_x = texture->width - tex_x - 1;
	}
	else if (game->ray.hit == 1)
	{
		if (game->ray.y > 0)
			tex_x = texture->width - tex_x - 1;
	}
	return (tex_x);
}

/** @brief Draws the ceiling and floor colors for a vertical 
 * stripe on the screen.
 * Fills pixels above draw_start with the ceiling color,
 * and pixels below draw_end with the floor color.
 * @param game Pointer to the game data struct containing image
 * buffer and colors.
 * @param draw_start The starting Y coordinate of the wall slice.
 * @param draw_end The ending Y coordinate of the wall slice.
 * @param x The current vertical stripe (column) being drawn*/
void	draw_ceiling_floor(t_data *game, int draw_start, int draw_end, int x)
{
	int	y;

	y = -1;
	while (++y < draw_start)
		game->ray.img_data[y * (game->minimap.size_line / 4) + x]
			= game->colors.c_hex;
	y = draw_end - 1;
	while (++y < HEIGHT)
		game->ray.img_data[y * (game->minimap.size_line / 4) + x]
			= game->colors.f_hex;
}
