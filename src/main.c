/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/19 12:53:48 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_move(t_data *game, double x, double y)
{
	int mx;
	int my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= game->width || my < 0 || my >= game->height)
		return (0);
	if (game->map[my][mx] == '1')
		return (0);
	game->px = x;
	game->py = y;
	return (1);
}

static int	key_hook(int keysym, t_data *game)
{
	double new_px;
	double new_py;

	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		game->player_angle -= ROT_SPEED;
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		game->player_angle += ROT_SPEED;
	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
	{
		new_px = game->px + cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py + sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
	{
		new_px = game->px - cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py - sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	render_map(game);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_data	game;

// 	if (argc != 2)
// 		return (printf("Usage: ./cub3d <map.cub>\n"));
// 	init_struct_game(&game);
// 	if (!valid_map(argv[1], &game))
// 	{
// 		game.init = mlx_init();
// 		if (game.init == NULL)
// 			return (printf("Error\nInitialization failed.\n"));
// 		game.window = mlx_new_window(game.init, 1920, 1080, "cub3D");
// 		if (game.window == NULL)
// 			return (mlx_destroy_display(game.init), free(game.init),
// 				printf("Error\nWindow creation failed.\n"));
// 		render_map(&game);
// 		mlx_key_hook(game.window, &key_hook, &game);
// 		mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
// 		mlx_loop(game.init);
// 	}
// 	return (free_map(game.map));
// }

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (printf("Usage: ./cub3d <map.cub>\n"));
	init_struct_game(&game);
	if (valid_map(argv[1], &game)) // returns 1 on error
		return (free_map(game.map), 1);
	game.init = mlx_init();
	if (!game.init)
		return (printf("Error\nInitialization failed.\n"));
	game.window = mlx_new_window(game.init, 1920, 1080, "cub3D");
	if (!game.window)
	{
		mlx_destroy_display(game.init);
		free(game.init);
		return (printf("Error\nWindow creation failed.\n"));
	}
	render_map(&game);
	mlx_key_hook(game.window, &key_hook, &game);
	mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
	mlx_loop(game.init);
	return (free_map(game.map), 0);
}
