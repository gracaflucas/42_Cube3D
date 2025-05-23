/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/05/23 16:50:58 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTES
// The AWSD keys are suppoused to move the player, the up|down|left|right keys are suppoused to turn left and right thru the map
#include "cub3D.h"

static int	is_valid_move(t_data *game, double new_x, double new_y)
{
	int	map_x = (int)new_x;
	int	map_y = (int)new_y;
	int	cur_x = (int)game->px;
	int	cur_y = (int)game->py;

	if (game->map_array[cur_y][map_x] != '1')
		game->px = new_x;
	if (game->map_array[map_y][cur_x] != '1')
		game->py = new_y;
	return (1);
}

static int	key_hook(int keysym, t_data *game)
{
	double	new_px;
	double	new_py;
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_Left)
		game->player_angle -= ROT_SPEED;
	if (keysym == XK_Right)
		game->player_angle += ROT_SPEED;
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
	if (keysym == KEY_D)
	{
		new_px = game->px + cos(game->player_angle + PI / 2) * MOVE_SPEED;
		new_py = game->py + sin(game->player_angle + PI / 2) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == KEY_A)
	{
		new_px = game->px + cos(game->player_angle - PI / 2) * MOVE_SPEED;
		new_py = game->py + sin(game->player_angle - PI / 2) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	return (render_map(game), 0);
}

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

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (printf("Usage: ./cub3d <map.cub>\n"));
	init_struct_game(&game);
	if (valid_map(argv[1], &game))
		return (free_matrix(game.map_array), 1);
	game.init = mlx_init();
	if (!game.init)
		return (printf("Error\nInitialization failed.\n"), 1);
	init_images(&game);
	game.window = mlx_new_window(game.init, 1920, 1080, "cub3D");
	if (!game.window)
		return (mlx_destroy_display(game.init), free(game.init),
			printf("Error\nWindow creation failed.\n"), 1);
	render_map(&game);
	mlx_key_hook(game.window, &key_hook, &game);
	mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
	mlx_loop(game.init);
	return (free_matrix(game.map_array), 0);
}
