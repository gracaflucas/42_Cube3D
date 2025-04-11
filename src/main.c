/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:12:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/11 12:37:47 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//alter the movement from wasd, to 'a' and 'd' rotation and 'w' and 's' to go back and forth
static int	key_hook(int keysym, t_data *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		if (game->py > 0 && game->map[game->px][game->py - 1] != '1')
		{
			game->player_angle = 'W';
			update_map(game, game->px, game->py - 1);
		}
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		if (game->py < game->width - 1
			&& game->map[game->px][game->py + 1] != '1')
		{
			game->player_angle = 'E';
			update_map(game, game->px, game->py + 1);
		}
	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
		if (game->px > 0 && game->map[game->px - 1][game->py] != '1')
		{
			game->player_angle = 'N';
			update_map(game, game->px - 1, game->py);
		}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
		if (game->px < game->height - 1
			&& game->map[game->px + 1][game->py] != '1')
		{
			game->player_angle = 'S';
			update_map(game, game->px + 1, game->py);
		}
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
		render_map(&game);
		mlx_key_hook(game.window, &key_hook, &game);
		mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
		mlx_loop(game.init);
	}
	return(free_map(game.map));
}
