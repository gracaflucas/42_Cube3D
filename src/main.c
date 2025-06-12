/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 11:57:07 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Checks whether the player can move to a new position on the map.
 * This function verifies if the destination coordinates (new_x, new_y)
 * are within walkable tiles ('1' indicates a wall) in the map. If movement 
 * is allowed, it updates the player's position accordingly.
 * @param game Pointer to the game state structure.
 * @param new_x Proposed new x-coordinate for the player.
 * @param new_y Proposed new y-coordinate for the player.
 * @return Always returns 1.*/
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

/** @brief Entry point for the cub3D application.
 * Initializes the game state, validates the map file, sets up graphics using
 * the MiniLibX library, and enters the main render and event loop.
 * @param argc Argument count.
 * @param argv Argument vector. Expects the second argument to be a map file.
 * @return 0 on success, 1 on failure (invalid arguments, map error, 
 * or init failure).*/
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
