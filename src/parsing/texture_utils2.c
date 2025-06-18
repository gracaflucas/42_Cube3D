/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:55:50 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/18 11:56:54 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Checks if a file exists and is accessible for reading.
 * Attempts to open the given file in read-only mode.
 * @param filename Path to the file.
 * @return 1 if the file exists, 0 otherwise.*/
int	file_exists(char *filename)
{
	FILE	*file;

	if (!filename)
		return (0);
	file = fopen(filename, "r");
	if (file)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

/** @brief Detects and throws an error if any texture or
 *  color directive is duplicated.
 * Scans the config file lines to ensure that each identifier 
 * (e.g., NO, SO, C) appears only once.
 * @param data Pointer to the main game data structure.*/
void	duplicate_texture_or_color(t_data *data)
{
	char	**file;
	int		i;
	int		j;

	i = -1;
	file = data->file;
	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") || ft_strstr(file[i], "SO ")
			|| ft_strstr(file[i], "EA ") || ft_strstr(file[i], "WE ")
			|| ft_strstr(file[i], "F ") || ft_strstr(file[i], "C "))
		{
			j = i;
			while (file[++j])
				if ((ft_strstr(file[i], "NO ") && ft_strstr(file[j], "NO "))
					|| (ft_strstr(file[i], "SO ") && ft_strstr(file[j], "SO "))
					|| (ft_strstr(file[i], "EA ") && ft_strstr(file[j], "EA "))
					|| (ft_strstr(file[i], "WE ") && ft_strstr(file[j], "WE "))
					|| (ft_strstr(file[i], "F ") && ft_strstr(file[j], "F "))
					|| (ft_strstr(file[i], "C ") && ft_strstr(file[j], "C ")))
					error_handler(data, "Duplicate texture or color");
		}
	}
}

/** @brief Validates that all texture paths exist and are readable.
 * Ensures that texture file paths (NO, SO, WE, EA) are all initialized
 * and refer to valid files. If any are missing or unreadable,
 *  triggers an error.
 * @param data Pointer to the main game data structure.*/
void	is_valid_textures(t_data *data)
{
	int	fd;
	int	i;

	if (!data->textures.files[0] || !data->textures.files[1]
		|| !data->textures.files[2] || !data->textures.files[3])
	{
		error_handler(data, "Missing texture");
	}
	i = 0;
	while (i < 4)
	{
		fd = open(data->textures.files[i], O_RDONLY);
		if (fd < 0)
		{
			error_handler(data, "Invalid texture file");
		}
		close(fd);
		i++;
	}
}
