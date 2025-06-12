/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:27:22 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:01:57 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

// reads a file line by line into a matrix (array of strings)
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
