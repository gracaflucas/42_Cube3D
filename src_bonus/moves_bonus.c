/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:15:23 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:16:10 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	move_up(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa) * MOVE_SPEED;
	new_py = game->py + sin(game->pa) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

static void	move_down(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px - cos(game->pa) * MOVE_SPEED;
	new_py = game->py - sin(game->pa) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

static void	move_right(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa + PI / 2) * MOVE_SPEED;
	new_py = game->py + sin(game->pa + PI / 2) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

static void	move_left(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa - PI / 2) * MOVE_SPEED;
	new_py = game->py + sin(game->pa - PI / 2) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

int	key_hook(int keysym, t_data *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_Left)
		game->pa -= ROT_SPEED;
	if (keysym == XK_Right)
		game->pa += ROT_SPEED;
	if (keysym == KEY_W)
		move_up(game);
	if (keysym == KEY_S)
		move_down(game);
	if (keysym == KEY_D)
		move_right(game);
	if (keysym == KEY_A)
		move_left(game);
	return (render_map(game), 0);
}
