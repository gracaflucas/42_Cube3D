/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:34:34 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/30 11:36:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Handles fatal errors by cleaning up resources and exiting.
 * Displays an error message (if provided), frees allocated resources
 * such as the map array, textures, images, window, and MLX context, 
 * then exits the program.
 * @param data Pointer to the main game data structure.
 * @param msg Optional error message to print to standard error.*/
void	error_handler(t_data *data, char *msg, char **file)
{
	if (msg)
	{
		write(STDERR_FILENO, "Error!\n", 7);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (file)
		free_matrix(file);
	if (data->map_array)
		free_matrix(data->map_array);
	free_textures(&data->textures, data->init);
	free(data->colors.ceiling);
	free(data->colors.floor);
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

/** @brief Frees memory and graphical resources used by texture images.
 * Destroys loaded images and frees associated texture file paths.
 * @param textures Pointer to the texture structure containing file
 *  paths and images.
 * @param mlx_ptr Pointer to the MLX context used for destroying images.*/
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

/** @brief Frees a NULL-terminated matrix of strings.
 * Iterates through each row in the matrix and frees it, then 
 * frees the matrix itself.
 * @param matrix Pointer to a NULL-terminated array of string pointers*/
void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

/** @brief Destroys minimap-related images if they exist
 * Uses MLX to destroy the minimap images and sets their pointers to NULL.
 * @param game Pointer to the main game structure.*/
static void	destroy_images(t_data *game)
{
	if (game->minimap.minimap)
		mlx_destroy_image(game->init, game->minimap.minimap);
	if (game->minimap.map)
		mlx_destroy_image(game->init, game->minimap.map);
	game->minimap.minimap = NULL;
	game->minimap.map = NULL;
}

/** @brief Cleans up all resources and exits the game safely.
 * This function is intended to be called when the user closes the game window.
 * It frees textures, color buffers, map data, MLX images, window, and context.
 * @param game Pointer to the main game structure.
 * @return Always returns 0 (though execution never continues after exit()).*/
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
