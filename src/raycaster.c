/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:42:07 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 11:27:10 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * Initializes the DDA algorithm by setting up ray direction, 
 step, and initial distances.
 * Description:
 *  This function prepares values needed for the DDA loop:
 *  - Computes ray direction components from the input angle
 * 		using cosine and sine.
 *  - Calculates `dx` and `dy`, which represent the distance the 
 * 		ray must travel 
 *    along X or Y to cross into the next map cell.
 *  - Determines the `step_x` and `step_y` directions (either -1 or +1),
 *    based on whether the ray is pointing left/right or up/down.
 *  - Computes `sx` and `sy`, the initial distances
 * 		to the first 
 *    x-side and y-side grid intersection.
 *
 * Notes:
 *  These values are reused by `perform_dda()` to incrementally
 * 	traverse the grid.
 */
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

/*
 * Performs DDA (Digital Differential Analyzer) algorithm 
 	to detect wall collisions.
 * Description:
 *  - Initializes the map grid position from the player's coordinates.
 *  - Calls `prepare_dda()` to set ray direction, step, and initial distances.
 *  - Iteratively steps through the grid by comparing side distances:
 *    - If `sx < sy`, the ray steps in X direction.
 *    - Otherwise, it steps in Y direction.
 *  - Stops when a wall ('1') is hit on the map.
 *  - Calculates the perpendicular distance from the player to the wall,
 *    used for perspective correction in the rendering step.
 *
 * Notes:
 *  The result of this function is used to determine wall height on screen.
 */
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
		if (g->ray.map_y >= g->height || g->ray.map_x >= g->width
			|| g->map_array[g->ray.map_y][g->ray.map_x] == '1')
			break ;
	}
	if (g->ray.hit == 0)
		g->ray.pd = (g->ray.sx - g->ray.dx) * cos(g->ray.angle - g->pa);
	else
		g->ray.pd = (g->ray.sy - g->ray.dy) * cos(g->ray.angle - g->pa);
}

/*
 * Determines the wall texture based on the ray's hit orientation.
 * Description:
 *  - Assigns a specific texture to each wall slice based on which 
 *    side of the wall
 *    the ray hit, relative to the player's view.
 *  - The `hit` flag identifies the type of wall hit:
 *      - `hit == 1` → horizontal wall (facing North or South).
 *      - `hit == 0` → vertical wall (facing East or West).
 *  - The direction the ray came from is inferred via `step_x` and `step_y`:
 *      - Horizontal hits:
 *          - `step_y > 0` → Ray hit a **North-facing** wall
 *          - `step_y < 0` → Ray hit a **South-facing** wall
 *      - Vertical hits:
 *          - `step_x > 0` → Ray hit a **West-facing** wall 
 *          - `step_x < 0` → Ray hit an **East-facing** wall
 */
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

/*
 * Draws a vertical wall slice on the screen at a given column.
 * Description:
 *  - This function fills one vertical column (`x`) of the screen image buffer
 *    with ceiling, wall, and floor colors, based on the calculated wall height
 *  - Calls `get_wall_color()` to determine the wall color based on 
 *    the ray's hit direction.
 *  - Fills pixels from top to `draw_start` with ceiling color (blue).
 *  - Fills pixels from `draw_start` to `draw_end` with the appropriate 
 *    wall color.
 *  - Fills pixels from `draw_end` to bottom of the screen with 
 *    floor color (gray).
 */
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

/*
 * Renders the full 3D view by casting rays and drawing wall columns on screen.
 * Description:
 *  - Destroys the previous frame image to avoid memory leaks.
 *  - Creates a new image buffer for the current frame.
 *  - Loops through each screen column (x = 0 to WIDTH):
 *      - Calculates the angle of the ray corresponding to that column.
 *      - Calls `perform_dda()` to detect the wall and get the perpendicular
 * 		  distance.
 *      - Uses the distance to compute the height of the wall to draw.
 *      - Calculates the vertical range (`draw_start` to `draw_end`) for the 
 *        wall slice.
 *      - Calls `get_wall_color()` to draw the ceiling, wall, and floor.
 *
 * Notes:
 *  - The number of rays is equal to the screen width 
 * 	  (one ray per vertical column).
 *  - The field of view is evenly divided across all rays.
 */
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
