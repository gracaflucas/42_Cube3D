/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:54 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 11:21:38 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
