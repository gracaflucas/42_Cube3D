/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:03:28 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/05/30 10:54:58 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	check_quad(double player_angle)
// {
// 	if (player_angle >= 0 && player_angle < PI_2)
// 		return (1);
// 	else if (player_angle >= PI_2 && player_angle < PI)
// 		return (2);
// 	else if (player_angle >= PI && player_angle < 3 * PI_2)
// 		return (3);
// 	else
// 		return (4);
// }

// void	move_player(int keysym, t_data *game)
// {
// 	int	quad;

// 	quad = check_quad(game->player_angle);
// 	if (keysym == KEY_W)
// 		return (move_up(game, quad));
// 	else if (keysym == KEY_S)
// 		return (move_down(game, quad));
// 	else if (keysym == KEY_A)
// 		return (move_left(game, quad));
// 	else if (keysym == KEY_D)
// 		return (move_right(game, quad));
// }


// void	move_up(t_data *game, int quad)
// {
// 	t_coordinate	new_pos;

// 	new_pos.x = game->player_pos.x;
// 	new_pos.y = game->player_pos.y;
// 	if (quad == 1)
// 	{
// 		new_pos.x += MOVE_SPEED * sin(game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(game->player_angle);
// 	}
// 	if (quad == 2)
// 	{
// 		new_pos.x += MOVE_SPEED * cos(game->player_angle - PI / 2);
// 		new_pos.y += MOVE_SPEED * sin(game->player_angle - PI / 2);
// 	}
// 	if (quad == 3)
// 	{
// 		new_pos.x -= MOVE_SPEED * cos((3 * PI / 2) - game->player_angle);
// 		new_pos.y += MOVE_SPEED * sin((3 * PI / 2) - game->player_angle);
// 	}
// 	if (quad == 4)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin((2 * PI) - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos((2 * PI) - game->player_angle);
// 	}
// 	return (change_player_position(&new_pos, game));
// }

// void	move_down(t_data *game, int quad)
// {
// 	t_coordinate	new_pos;

// 	new_pos.x = game->player_pos.x;
// 	new_pos.y = game->player_pos.y;
// 	if (quad == 1)
// 	{
// 		new_pos.x += MOVE_SPEED * sin(game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(game->player_angle);
// 	}
// 	if (quad == 2)
// 	{
// 		new_pos.x += MOVE_SPEED * cos(game->player_angle - PI / 2);
// 		new_pos.y += MOVE_SPEED * sin(game->player_angle - PI / 2);
// 	}
// 	if (quad == 3)
// 	{
// 		new_pos.x -= MOVE_SPEED * cos((3 * PI / 2) - game->player_angle);
// 		new_pos.y += MOVE_SPEED * sin((3 * PI / 2) - game->player_angle);
// 	}
// 	if (quad == 4)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin((2 * PI) - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos((2 * PI) - game->player_angle);
// 	}
// 	return (change_player_position(&new_pos, game));
// }

// void	move_left(t_data *game, int quad)
// {
// 	t_coordinate	new_pos;

// 	new_pos.x = game->player_pos.x;
// 	new_pos.y = game->player_pos.y;
// 	if (quad == 1)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(PI / 2 - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(PI / 2 - game->player_angle);
// 	}
// 	if (quad == 2)
// 	{
// 		new_pos.x += MOVE_SPEED * sin(game->player_angle - PI / 2);
// 		new_pos.y -= MOVE_SPEED * cos(game->player_angle- PI / 2);
// 	}
// 	if (quad == 3)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(PI / 2 - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(PI / 2 - game->player_angle);
// 	}
// 	if (quad == 4)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(game->player_angle - (3 * PI / 2));
// 		new_pos.y += MOVE_SPEED * cos(game->player_angle - (3 * PI / 2));
// 	}
// 	return (change_player_position(&new_pos, game));
// }

// void	move_right(t_data *game, int quad)
// {
// 	t_coordinate	new_pos;

// 	new_pos.x = game->player_pos.x;
// 	new_pos.y = game->player_pos.y;
// 	if (quad == 1)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(PI / 2 - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(PI / 2 - game->player_angle);
// 	}
// 	if (quad == 2)
// 	{
// 		new_pos.x += MOVE_SPEED * sin(game->player_angle - PI / 2);
// 		new_pos.y -= MOVE_SPEED * cos(game->player_angle- PI / 2);
// 	}
// 	if (quad == 3)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(PI / 2 - game->player_angle);
// 		new_pos.y -= MOVE_SPEED * cos(PI / 2 - game->player_angle);
// 	}
// 	if (quad == 4)
// 	{
// 		new_pos.x -= MOVE_SPEED * sin(game->player_angle - (3 * PI / 2));
// 		new_pos.y += MOVE_SPEED * cos(game->player_angle - (3 * PI / 2));
// 	}
// 	return (change_player_position(&new_pos, game));
// }

// void	change_player_position(t_coordinate *new_pos, t_data *game)
// {
// 	char	possible_new_pos;
// 	char	possible_new_pos_x;
// 	char	possible_new_pos_y;

// 	possible_new_pos = game->map_array[(int)new_pos->y][(int)new_pos->x];
// 	possible_new_pos_x = game->map_array[(int)game
// 		->player_pos.y][(int)new_pos->x];
// 	possible_new_pos_y = game->map_array[(int)new_pos
// 		->y][(int)game->player_pos.x];
// 	if (possible_new_pos && possible_new_pos != WALL
// 		&& possible_new_pos_x != WALL && possible_new_pos_y != WALL)
// 	{
// 		game->player_pos.x = new_pos->x;
// 		game->player_pos.y = new_pos->y;
// 		walk_move(game);
// 	}
// }

// void	walk_move(t_data *game)
// {
// 	static int	old_mov = 5;

// 	if (game->movement <= old_mov && game->movement <= 5)
// 		game->movement ++;
// 	else if (game->movement >= old_mov && game->movement >= 0)
// 		game->movement --;
// 	if (game->movement == 5)
// 		old_mov = 0;
// 	if (game->movement == 0)
// 		old_mov = 5;
// }


/* double	new_px;
	double	new_py;

	if (keysym == KEY_W)
	{
		new_px = game->px + cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py + sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == KEY_S)
	{
		new_px = game->px - cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py - sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == KEY_A)
	{
		new_px = game->px + cos(PI / 2 - game->player_angle) * MOVE_SPEED;
		new_py = game->py + sin(PI / 2 - game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == KEY_D)
	{
		new_px = game->px + cos(PI / 2 - game->player_angle) * MOVE_SPEED;
		new_py = game->py + sin(PI / 2 - game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	} */

    // static int	key_hook(int keysym, t_data *game)
// {
	// 	if (keysym == XK_Escape)
	// 		close_window(game);
	// 	if (keysym == XK_Left)
	// 		game->player_angle -= ROT_SPEED;
	// 	if (keysym == XK_Right)
	// 		game->player_angle += ROT_SPEED;
	// 	if (keysym == KEY_W || keysym == KEY_S || keysym == KEY_A || keysym == KEY_D)
	// 		move_player(keysym, game);
	// 	return (render_map(game), 0);
	// }