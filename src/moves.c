/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:03:28 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 12:16:49 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Moves the player forward in the direction they are facing.
 * Calculates the new position using the player's angle and MOVE_SPEED,
 * then validates and updates the player's position.
 * @param game Pointer to the game state.*/
static void	move_up(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa) * MOVE_SPEED;
	new_py = game->py + sin(game->pa) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

/** @brief Moves the player backward opposite to the direction they are facing.
 * Calculates the new position using the player's angle and MOVE_SPEED,
 * then validates and updates the player's position.
 * @param game Pointer to the game state.*/
static void	move_down(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px - cos(game->pa) * MOVE_SPEED;
	new_py = game->py - sin(game->pa) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

/** @brief Moves the player to the right relative to their facing direction.
 * Calculates the new position perpendicular to the player's angle (+90 degrees)
 * and validates the move.
 * @param game Pointer to the game state.*/
static void	move_right(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa + PI / 2) * MOVE_SPEED;
	new_py = game->py + sin(game->pa + PI / 2) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

/** @brief Moves the player to the left relative to their facing direction.
 * Calculates the new position perpendicular to the player's angle (-90 degrees)
 * and validates the move.
 * @param game Pointer to the game state.*/
static void	move_left(t_data *game)
{
	double	new_px;
	double	new_py;

	new_px = game->px + cos(game->pa - PI / 2) * MOVE_SPEED;
	new_py = game->py + sin(game->pa - PI / 2) * MOVE_SPEED;
	is_valid_move(game, new_px, new_py);
}

/** @brief Handles keyboard input for movement and rotation.
 * - Esc closes the game.
 * - Left/Right arrows rotate the player.
 * - W/S move forward/backward.
 * - A/D strafe left/right.
 * After processing input, triggers rendering of the updated view.
 * @param keysym Key code of the pressed key.
 * @param game Pointer to the game state.
 * @return Always returns 0.*/
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
