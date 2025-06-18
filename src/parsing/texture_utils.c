/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:10:21 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/18 11:42:00 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_colors(t_data *data, int start)
{
	char	**file;

	file = data->file;
	while (file[start])
	{
		if (ft_strstr(file[start], "F ") && !data->colors.floor)
			data->colors.floor = get_info(file[start], 1);
		else if (ft_strstr(file[start], "C ") && !data->colors.ceiling)
			data->colors.ceiling = get_info(file[start], 1);
		else if (ft_strchr("01NSEW", file[start][0]))
			return (-1);
		if (data->colors.floor && data->colors.ceiling)
			return (start + 1);
		start++;
	}
	return (0);
}

static int	init_textures(t_data *data)
{
	int		i;
	char	**file;

	i = -1;
	file = data->file;
	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") && !data->textures.files[0])
			data->textures.files[0] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "EA ") && !data->textures.files[1])
			data->textures.files[1] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "SO ") && !data->textures.files[2])
			data->textures.files[2] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "WE ") && !data->textures.files[3])
			data->textures.files[3] = get_info(file[i], 2);
		else if (ft_strchr("01NSEW", file[i][0]))
			return (-1);
		if (data->textures.files[0] && data->textures.files[1]
			&& data->textures.files[2] && data->textures.files[3])
			return (i + 1);
	}
	return (0);
}

/** @brief Initializes texture file paths and color values
 *  from map file lines.
 * Parses each line in the map file to find texture and colo
 *  definitions (NO, SO, WE, EA, F, C).
 * Stops early once all six required definitions are found.
 * @param data Pointer to the main game data structure.
 * @return Index of the next unprocessed line, or 0 if incomplete.*/
int	init_texture_color_names(t_data *data)
{
	int	idx;

	idx = init_textures(data);
	if (idx <= 0)
		return (0);
	idx = init_colors(data, idx);
	if (idx <= 0)
		return (0);
	return (idx);
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
