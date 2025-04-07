/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/07 13:11:48 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	key_hook(int keysym, t_data *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (printf("Error\nWrong Command Line Argument.\n"));
	init_struct_game(&game);
	readmap(argv[1], &game);
	if (!valid_map(argv[1], &game))
	{
		game.init = mlx_init();
		if (game.init == NULL)
			return (printf("Error\nInitialization failed.\n"));
		game.window = mlx_new_window(game.init, 1920, 1080, "cub3D");
		if (game.window == NULL)
		{
			mlx_destroy_display(game.init);
			free(game.init);
			return (printf("Error\nWindow creation failed.\n"));
		}
		//init game
		mlx_key_hook(game.window, &key_hook, &game);
		mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
		mlx_loop(game.init);
	}
	return(free_map(game.map));
}
