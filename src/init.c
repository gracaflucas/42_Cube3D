/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:55:12 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/11 12:19:41 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_struct_game(t_data *game)
{
	if (game == NULL)
		return ;
	game->window = NULL;
	game->init = NULL;
	game->map_img = NULL;
	game->map = NULL;
	game->px = 0;
	game->py = 0;
	game->player = 0;
	game->player_angle = 0;
	game->height = 0;
	game->width = 0;
}

static void	destroy_images(t_data *game)
{
	if (game->map_img)
		mlx_destroy_image(game->init, game->map_img);
	game->map_img = NULL;
}

int	close_window(t_data *game)
{
	destroy_images(game);
	mlx_destroy_window(game->init, game->window);
	mlx_destroy_display(game->init);
	free_map(game->map);
	free(game->init);
	game->init = NULL;
	exit(0);
}

int	free_map(char **map)
{
	int	i;

	if (map == NULL)
		return (1);
	i = -1;
	while (map[++i] != NULL)
		free(map[i]);
	free(map);
	return (0);
}
