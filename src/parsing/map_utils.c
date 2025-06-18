/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:06:18 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/17 13:35:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// usar error_handler e nao printf

/** @brief Extracts and prepares the map from the file starting at start_y line.
 * Validates map characters, calculates map dimensions, 
 * pads lines to equal length,
 * and returns a newly allocated 2D char array representing the map.
 * @param game Pointer to the game structure (to store map dimensions).
 * @param file The array of strings read from the file.
 * @param start_y The line index where the map starts in the file.
 * @return Newly allocated map matrix, or NULL on failure or invalid map. */
char	**extract_map(t_data *game, char **file, int start_y)
{
	char	**map;
	int		map_height;
	int		max_len;
	int		i;

	map_height = map_size_valid_char(file, start_y);
	if (map_height <= 0)
		return (free_matrix(file),
			error_handler(game, "Invalid character or empty map."), NULL);
	game->height = map_height;
	max_len = find_biggest_line(&file[start_y]);
	game->width = max_len;
	map = ft_calloc(sizeof(char *), map_height + 1);
	if (!map)
		return (error_handler(game, "Memory allocation failed for map."), NULL);
	i = -1;
	while (++i < map_height)
	{
		map[i] = get_map_line(file[start_y + i], max_len);
		if (!map[i])
			return (free_matrix(map),
				error_handler(game, "Line allocation failed."), NULL);
	}
	return (map);
}

/** @brief Finds the length of the longest line in the map.
 * Used to pad shorter lines to ensure rectangular map shape.
 * @param file The map lines starting from map start.
 * @return The length of the longest line (excluding newline).*/
int	find_biggest_line(char **file)
{
	int	i;
	int	max_len;
	int	len;

	i = 0;
	max_len = 0;
	while (file[i])
	{
		len = 0;
		while (file[i][len] && file[i][len] != '\n')
			len++;
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

/** @brief Counts valid map lines starting at start_y.
 * Checks that each character in these lines is valid for the map.
 * Valid characters: ' ', '0', '1', 'N', 'S', 'E', 'W', '\t', '\n', 'D'.
 * @param file The entire file as an array of strings.
 * @param start_y The index in file where the map starts.
 * @return Number of valid map lines, or 0 if invalid character found.*/
int	map_size_valid_char(char **file, int start_y)
{
	int	i;
	int	j;
	int	lines;

	lines = 0;
	i = start_y;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] != ' ' && file[i][j] != '0' && file[i][j] != '1'
				&& file[i][j] != 'N' && file[i][j] != 'S'
				&& file[i][j] != 'E' && file[i][j] != 'W'
				&& file[i][j] != '\t' && file[i][j] != '\n'
				&& file[i][j] != 'D')
				return (0);
			j++;
		}
		lines++;
		i++;
	}
	return (lines);
}

/** @brief Copies and pads a single map line to a specified size.
 * Pads shorter lines with spaces to ensure consistent map width.
 * @param file_line The source map line string.
 * @param size Desired length of the line after padding.
 * @return Newly allocated padded line string, or NULL on allocation failure.*/
char	*get_map_line(char *file_line, int size)
{
	char	*line;
	int		i;

	line = ft_calloc(sizeof(char), size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (file_line[i] && file_line[i] != '\n')
	{
		line[i] = file_line[i];
		i++;
	}
	while (i < size)
		line[i++] = ' ';
	return (line);
}

/** @brief Checks if the given coordinates are within the bounds of the map.
 * @param g Pointer to the game structure containing map dimensions.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return 1 if (x,y) is inside the map bounds, 0 otherwise.*/
int	is_in_bounds(t_data *g, int x, int y)
{
	return (x >= 0 && y >= 0 && y < g->height && x < g->width);
}
