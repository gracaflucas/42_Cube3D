/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:34:34 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/19 16:11:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void error_handler(t_data *data, char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, "Error!\n", 7);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	if (data->map)
		free_map(data->map);
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
	free(data);
	exit(EXIT_FAILURE);
}

void free_textures(t_texture *textures, void *mlx_ptr)
{
	int i;

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

int free_map(char **map)
{
	int i;

	if (map == NULL)
		return (1);
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (0);
}
