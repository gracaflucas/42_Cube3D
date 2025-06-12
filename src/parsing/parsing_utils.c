/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:06:18 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 12:32:23 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Recursively checks if the map is enclosed using a
 *  flood-fill approach.
 * Marks visited tiles with 'X'. Only walkable tiles ('0', player start)
 *  are explored.
 * If any path leads outside bounds or to a space, the map is invalid.
 * @param map The 2D map array (char matrix).
 * @param g Pointer to the game data (for map bounds).
 * @param x Current X coordinate.
 * @param y Current Y coordinate.
 * @return 1 if map is enclosed at this path, 0 if a leak is found.*/
int	is_flood_valid(char **map, t_data *g, int x, int y)
{
	if (!is_in_bounds(g, x, y))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	return (is_flood_valid(map, g, x + 1, y)
		&& is_flood_valid(map, g, x - 1, y)
		&& is_flood_valid(map, g, x, y + 1)
		&& is_flood_valid(map, g, x, y - 1));
}

/** @brief Reads a text file into a NULL-terminated array of strings.
 * Each line from the file becomes one element in the array.
 *  The caller must free the matrix.
 * @param file Path to the file.
 * @return A NULL-terminated array of strings (matrix), or NULL on failure.*/
char	**read_file_to_matrix(char *file)
{
	int		fd;
	int		i;
	int		lines;
	char	**matrix;
	char	*line;

	lines = count_file_lines(file);
	if (lines <= 0)
		return (NULL);
	matrix = malloc(sizeof(char *) * (lines + 1));
	if (!matrix)
		return (NULL);
	fd = open(file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		matrix[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	matrix[i] = NULL;
	close(fd);
	return (matrix);
}

/** @brief Counts the number of lines in a file.
 * Opens the file and reads line by line to count how many lines it has.
 * @param file The file path to count lines from.
 * @return Number of lines, or -1 on error. */
int	count_file_lines(char *file)
{
	int		counter;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
	counter = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		counter++;
		free (line);
	}
	free (line);
	close (fd);
	return (counter);
}

/** @brief Recursively fills reachable spaces on the map starting at (x, y).
 * Used to determine if the player is surrounded by closed
 *  walls. Fills walkable
 * tiles with 'F' and stops on walls, already filled, or empty space.
 * @param map The 2D map array.
 * @param y Y-coordinate to start flood fill.
 * @param x X-coordinate to start flood fill.*/
void	fill_recursive(char **map, int y, int x)
{
	if (!map || y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == ' ')
		return ;
	map[y][x] = 'F';
	fill_recursive(map, y + 1, x);
	fill_recursive(map, y - 1, x);
	fill_recursive(map, y, x + 1);
	fill_recursive(map, y, x - 1);
}

/** @brief Duplicates a map matrix into a new memory space.
 * Creates a deep copy of a 2D char array (up to given height).
 * @param src The source map matrix.
 * @param height Number of rows in the map.
 * @return A new duplicated matrix, or NULL on allocation failure.*/
char	**duplicate_map(char **src, int height)
{
	char	**copy;
	int		i;

	copy = ft_calloc(height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (free_matrix(copy), NULL);
	}
	return (copy);
}
