/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 11:03:23 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTES
// Ignore the moves.c file, it is not working, I'll keep it just in case
// movement is working and its not crossing walls, but zooming in and out of 
// walls still looks funny, sometimes it slips the walls like corners,
// and we always lose quality. The AWSD keys are suppoused to move the player,
// the left|right keys are suppoused 
//to rotate left and right thru the map
#include "cub3D.h"

int	is_valid_move(t_data *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;
	int	cur_x;
	int	cur_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	cur_x = (int)game->px;
	cur_y = (int)game->py;
	if (game->map_array[cur_y][map_x] != '1')
		game->px = new_x;
	if (game->map_array[map_y][cur_x] != '1')
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
	mlx_loop(game.init);
	return (free_matrix(game.map_array), 0);
}
