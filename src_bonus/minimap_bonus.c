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

#include "cub3D_bonus.h"

/* Draws a single tile of the minimap based on the map character at the given 
	coordinates.
 * Description:
 *  The function checks the character at position (i, j) in the map.
 *  - If it is a direction character ('N', 'S', 'W', 'E'), it's treated as 
 * 	an empty tile ('0').
 *  - Depending on whether the tile is empty ('0') or a wall ('1'), 
 * 	a corresponding color is chosen.
 *  - Then, the function calculates the pixel offset on the image and draws a
 * 	 23x23 pixel square
 *    representing that tile in the minimap.
 *
 * Tile color codes:
 *  - '0': Black (empty space)
 *  - '1': White (wall)
 */
static void	draw_tile(t_data *game, int i, int j, int *img_data)
{
	char	c;
	int		x;
	int		y;

	c = game->map_array[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		c = '0';
		game->map_array[i][j] = '0';
	}
	if (c == '0')
		game->minimap.pixel_color = 0x000000;
	else if (c == '1')
		game->minimap.pixel_color = 0xFFFFFF;
	game->minimap.x_offset = j * 24;
	game->minimap.y_offset = i * 24;
	y = -1;
	while (++y < 23)
	{
		x = -1;
		while (++x < 23)
			img_data[(game->minimap.y_offset + y)
				* (game->minimap.size_line / 4) + (game->minimap.x_offset + x)]
				= game->minimap.pixel_color;
	}
}

/*
 * Draws the player as a small square on the minimap.
 * Description:
 *  The function draws a square (10x10 pixels) centered around the 
 * 	player's position on the minimap.
 *  - The player's position (game->px, game->py) is scaled to match
 * 	 the minimap tile size (24 pixels).
 *  - For each pixel in the square, it checks if it's within the bounds 
 * 	of the minimap.
 *  - If within bounds, the pixel is colored yellow (0xFFFF00) to represent 
 * 	the player's location.
 *
 * Notes:
 *  - The player is always drawn on top of the map tiles.
 */
static void	draw_player(t_data *game, int *img_data)
{
	int	player_size;
	int	x;
	int	y;
	int	draw_x;
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
				img_data[draw_y * (game->minimap.size_line / 4) + draw_x]
					= 0xFFFF00;
		}
	}
}

/*
 *	Casts a single ray from the player's position at a given angle, 
 	and draws it on the minimap.
 *	Description:
 * This function simulates raycasting from the player's position 
 * to detect walls on the map.
 * - The ray advances in small steps (0.05 units) along the specified angle.
 * - At each step, the ray's current map tile is checked.
 *    - If the ray hits a wall ('1'), the loop breaks.
 * - For each step, the ray's position is converted to pixel coordinates 
 *   (scaled by tile size: 24).
 * - A green pixel (0x00FF00) is drawn at each step on the minimap 
 *   to visualize the ray path.
 */
static void	cast_ray(t_data *game, double angle)
{
	game->ray.x = game->px;
	game->ray.y = game->py;
	game->ray.angle = angle;
	while (1)
	{
		game->ray.mx = (int)game->ray.x;
		game->ray.my = (int)game->ray.y;
		if (game->map_array[game->ray.my][game->ray.mx] == '1')
			break ;
		game->ray.pixel_x = game->ray.x * 24;
		game->ray.pixel_y = game->ray.y * 24;
		game->ray.img_data = (int *)mlx_get_data_addr(game->minimap.minimap,
				&(int){0}, &game->minimap.size_line, &(int){0});
		game->ray.img_data[game->ray.pixel_y * (game->minimap.size_line / 4)
			+ game->ray.pixel_x] = 0x00FF00;
		game->ray.x += cos(game->ray.angle) * 0.05;
		game->ray.y += sin(game->ray.angle) * 0.05;
	}
}

/*
 * Casts multiple rays across the player's field of view (FOV)
   to simulate vision.
 * Description:
 *  This function sweeps a series of rays across the player's
 *  current field of view.
 *  - It starts from an angle slightly to the left of the player’s direction
 *    (player_angle - FOV / 2) and ends slightly to the right.
 *  - A total of 1080 rays are cast (1 per pixel of screen width).
 *  - Each ray is cast at a small increment of angle (step),
 *    and handled by `cast_ray()`.
 *
 * Notes:
 *  - This creates the visual effect of a cone-shaped field of vision.
 *  - The number 1080 usually corresponds to the screen width in pixels.
 */
static void	cast_fov(t_data *game)
{
	double	start_angle;
	double	updated_angle;
	double	step;
	int		i;

	start_angle = game->pa - (FOV / 2);
	step = FOV / 1920;
	i = -1;
	while (++i < 1920)
	{
		updated_angle = start_angle + i * step;
		cast_ray(game, updated_angle);
	}
}

/*
 * Renders the full minimap, including the map tiles, player, 
   and field of view (FOV).
 * Description:
 *  This function handles the rendering of the entire minimap each frame.
 *  - First, it destroys the previous minimap image if it exists 
 *    to prevent memory leaks.
 *  - Then, it creates a new image buffer sized to the map dimensions 
 *    (scaled by 24 pixels per tile).
 *  - For each map tile, `draw_tile()` is called to draw the appropriate 
 *    square on the minimap.
 *  - After the tiles, `draw_player()` draws the player 
 *    at their current position.
 *  - Then, `cast_fov()` draws rays from the player across their field of view.
 *  - Finally, the completed minimap image is pushed to the game window 
 *    using `mlx_put_image_to_window()`.
 *
 * Notes:
 *  - Tile size is fixed at 24x24 pixels.
 */
void	render_minimap(t_data *game)
{
	int	*img_data;
	int	i;
	int	j;

	i = -1;
	if (game->minimap.minimap)
		mlx_destroy_image(game->init, game->minimap.minimap);
	game->minimap.minimap = mlx_new_image(game->init,
			game->width * 24, game->height * 24);
	img_data = (int *)mlx_get_data_addr(game->minimap.minimap, &j,
			&game->minimap.size_line, &j);
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
			draw_tile(game, i, j, img_data);
	}
	draw_player(game, img_data);
	cast_fov(game);
	render_minimap(game);
}
