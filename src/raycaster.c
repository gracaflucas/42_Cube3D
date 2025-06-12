/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:42:07 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:14:00 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Initializes the DDA algorithm by setting up ray direction,
 *  step, and initial distances.
 * This function prepares the values needed for the DDA loop:
 * - Computes ray direction components from the input angle using cosine and sine.
 * - Calculates `dx` and `dy`, which represent the distance the ray must travel
 *   along X or Y to cross into the next map cell.
 * - Determines the `step_x` and `step_y` directions (either -1 or +1),
 *   based on the ray direction.
 * - Computes `sx` and `sy`, the initial distances to the first
 *  x-side and y-side grid intersections.
 * These values are used by `perform_dda()` to traverse the grid.
 * @param game Pointer to the main game struct.
 * @param ray_angle The angle at which the ray is cast.*/
static void	prepare_dda(t_data *game, double ray_angle)
{
	game->ray.x = cos(ray_angle);
	game->ray.y = sin(ray_angle);
	game->ray.dx = fabs(1 / game->ray.x);
	game->ray.dy = fabs(1 / game->ray.y);
	if (game->ray.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.sx = (game->px - game->ray.map_x) * game->ray.dx;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.sx = (game->ray.map_x + 1.0 - game->px) * game->ray.dx;
	}
	if (game->ray.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.sy = (game->py - game->ray.map_y) * game->ray.dy;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.sy = (game->ray.map_y + 1.0 - game->py) * game->ray.dy;
	}
}

/** @brief Performs the DDA (Digital Differential Analyzer) algorithm to detect wall collisions.
 * - Initializes the grid position from the player's coordinates.
 * - Calls `prepare_dda()` to set ray direction, step, and initial
 *  distances.
 * - Steps through the grid, advancing along the axis with the smaller
 *  next side distance.
 * - Stops when a wall ('1') is hit.
 * - Calculates the perpendicular distance from the player to the
 *  wall for perspective correction.
 * @param g Pointer to the main game struct.
 * @param ray_angle The angle at which the ray is cast.*/
void	perform_dda(t_data *g, double ray_angle)
{
	g->ray.map_x = (int)g->px;
	g->ray.map_y = (int)g->py;
	prepare_dda(g, ray_angle);
	while (1)
	{
		if (g->ray.sx < g->ray.sy)
		{
			g->ray.sx += g->ray.dx;
			g->ray.map_x += g->ray.step_x;
			g->ray.hit = 0;
		}
		else
		{
			g->ray.sy += g->ray.dy;
			g->ray.map_y += g->ray.step_y;
			g->ray.hit = 1;
		}
		if (g->ray.map_y >= g->height || g->ray.map_x >= g->width || g->ray.map_x < 0 
		|| g->ray.map_y < 0 || g->map_array[g->ray.map_y][g->ray.map_x] == '1')
			break;
	}
	if (g->ray.hit == 0)
		g->ray.pd = (g->ray.sx - g->ray.dx) * cos(g->ray.angle - g->pa);
	else
		g->ray.pd = (g->ray.sy - g->ray.dy) * cos(g->ray.angle - g->pa);
}

/** @brief Determines which wall texture to use based on the ray's hit orientation.
 *
 * Uses the `hit` flag and ray step directions to assign textures:
 * - Horizontal hits (hit == 1):
 *   - step_y > 0: North-facing wall texture
 *   - step_y < 0: South-facing wall texture
 * - Vertical hits (hit == 0):
 *   - step_x > 0: West-facing wall texture
 *   - step_x < 0: East-facing wall texture
 * @param game Pointer to the main game struct.
 * @return Pointer to the selected texture image.*/
static t_image	*get_wall_texture(t_data *game)
{
	if (game->ray.hit == 1)
	{
		if (game->ray.step_y > 0)
			return (&game->textures.images[2]);
		else
			return (&game->textures.images[0]);
	}
	else if (game->ray.hit == 0)
	{
		if (game->ray.step_x > 0)
			return (&game->textures.images[1]);
		else
			return (&game->textures.images[3]);
	}
	return (NULL);
}

/** @brief Draws a vertical wall slice on the screen at column `x`.
 * - Calculates texture coordinates and steps.
 * - Fills pixels above the wall slice with the ceiling color.
 * - Fills the wall slice using texture sampling.
 * - Fills pixels below the wall slice with the floor color.
 * @param game Pointer to the main game struct.
 * @param draw_start Y coordinate to start drawing the wall.
 * @param draw_end Y coordinate to end drawing the wall.
 * @param x Current screen column being drawn.*/
static void	draw_wall(t_data *game, int draw_start, int draw_end, int x)
{
	t_image	*t;
	char	*pxl;
	int		y;
	double	step;
	double	tex_pos;

	calc_lines(game);
	t = get_wall_texture(game);
	t->tex_x = flip_textures(t, game);
	step = 1.0 * t->height / game->line_height;
	tex_pos = (draw_start - game->unclipped_start) * step;
	draw_ceiling_floor(game, draw_start, draw_end, x);
	y = draw_start - 1;
	while (++y < draw_end)
	{
		t->tex_y = (int)tex_pos;
		if (t->tex_y < 0)
			t->tex_y = 0;
		if (t->tex_y >= t->height)
			t->tex_y = t->height - 1;
		tex_pos += step;
		pxl = t->addr + (t->tex_y * t->llen + t->tex_x * (t->bpp / 8));
		t->color = *(unsigned int *)pxl;
		game->ray.img_data[y * (game->minimap.size_line / 4) + x] = t->color;
	}
}

/** @brief Renders the full 3D view by casting rays and 
 * drawing vertical slices.
 * - Destroys previous frame image and creates a new one.
 * - For each vertical column on screen:
 *   - Calculates the ray angle.
 *   - Performs DDA to find wall collisions and distance.
 *   - Calculates wall slice height.
 *   - Draws ceiling, wall, and floor for that column.
 * - Puts the rendered image onto the window.
 * @param game Pointer to the main game struct.*/
void	render_map(t_data *game)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	x;

	if (game->minimap.map)
		mlx_destroy_image(game->init, game->minimap.map);
	game->minimap.map = mlx_new_image(game->init, WIDTH, HEIGHT);
	game->ray.img_data = (int *)mlx_get_data_addr(game->minimap.map,
			&(int){0}, &game->minimap.size_line, &(int){0});
	x = -1;
	while (++x < WIDTH)
	{
		game->ray.angle = game->pa - (FOV / 2) + x * (FOV / WIDTH);
		perform_dda(game, game->ray.angle);
		line_height = (int)(HEIGHT / game->ray.pd);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		draw_wall(game, draw_start, draw_end, x);
	}
	mlx_put_image_to_window(game->init, game->window, game->minimap.map, 0, 0);
}
