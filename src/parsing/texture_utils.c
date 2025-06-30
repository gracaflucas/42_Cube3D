/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:10:21 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/18 16:46:48 by marvin           ###   ########.fr       */
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

int	first_map_check(t_data *game, char **file, int start_y)
{
	int	map_height;
	int	max_len;

	if (!validate_map_continuity(file, start_y))
		return (free_matrix(file),
			error_handler(game, "Map has empty lines."), 1);
	map_height = map_size_valid_char(file, start_y);
	if (map_height <= 0)
		return (free_matrix(file),
			error_handler(game, "Invalid character or empty map."), 1);
	game->height = map_height;
	max_len = find_biggest_line(&file[start_y]);
	game->width = max_len;
	return (0);
}
