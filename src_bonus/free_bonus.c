/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:34:34 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 12:03:28 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	error_handler(t_data *data, char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, "Error!\n", 7);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (data->map_array)
		free_matrix(data->map_array);
	free_textures(&data->textures, data->init);
	if (data->minimap.minimap)
		mlx_destroy_image(data->init, data->minimap.minimap);
	if (data->minimap.map)
		mlx_destroy_image(data->init, data->minimap.map);
	if (data->window)
		mlx_destroy_window(data->init, data->window);
	if (data->init)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	exit(EXIT_FAILURE);
}

void	free_textures(t_texture *textures, void *mlx_ptr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures->files[i])
		{
			free(textures->files[i]);
			textures->files[i] = NULL;
		}
		if (textures->images[i].img)
		{
			mlx_destroy_image(mlx_ptr, textures->images[i].img);
			textures->images[i].img = NULL;
		}
		i++;
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

static void	destroy_images(t_data *game)
{
	if (game->minimap.minimap)
		mlx_destroy_image(game->init, game->minimap.minimap);
	if (game->minimap.map)
		mlx_destroy_image(game->init, game->minimap.map);
	game->minimap.minimap = NULL;
	game->minimap.map = NULL;
}

int	close_window(t_data *game)
{
	destroy_images(game);
	free_textures(&game->textures, game->init);
	free(game->colors.ceiling);
	free(game->colors.floor);
	if (game->file)
		free_matrix(game->file);
	mlx_destroy_window(game->init, game->window);
	mlx_destroy_display(game->init);
	free_matrix(game->map_array);
	free(game->init);
	game->init = NULL;
	exit(0);
}
