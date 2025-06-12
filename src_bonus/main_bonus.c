/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:30:55 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/30 12:30:55 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	mouse_move_hook(int x, int y, t_data *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	game->pa += delta_x * ROT_SPEED / 1500;
	render_map(game);
	render_minimap(game);
	return (0);
}

int	is_valid_move(t_data *game, double new_x, double new_y)
{
	int	mx;
	int	my;
	int	cur_x;
	int	cur_y;

	mx = (int)new_x;
	my = (int)new_y;
	cur_x = (int)game->px;
	cur_y = (int)game->py;
	if (game->map_array[cur_y][mx] != '1')
		game->px = new_x;
	if (game->map_array[my][cur_x] != '1')
		game->py = new_y;
	return (1);
}

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
	mlx_hook(game.window, 6, 1L << 6, mouse_move_hook, &game);
	mlx_loop(game.init);
	return (free_matrix(game.map_array), 0);
}
