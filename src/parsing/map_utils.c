/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:06:18 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/05/06 10:16:53 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 	Takes the map part and normalizes it (copy + pad)
// Add this to your header or top of file if needed

char	**extract_map(t_data *game, char **file, int start_y)
{
	char	**map;
	int		map_height;
	int		max_len;
	int		i;

	map_height = map_size_valid_char(file, start_y);
	if (map_height <= 0)
		return (printf("Error\nInvalid character or empty map.\n"), NULL);
	game->height = map_height;
	max_len = find_biggest_line(&file[start_y]);
	game->width = max_len;
	map = ft_calloc(sizeof(char *), map_height + 1);
	if (!map)
		return (printf("Error\nMemory allocation failed for map.\n"), NULL);
	i = -1;
	while (++i < map_height)
	{
		map[i] = get_map_line(file[start_y + i], max_len);
		if (!map[i])
			return (free_matrix(map),
				printf("Error\nLine allocation failed.\n"), NULL);
	}
	return (map);
}

// 	Finds the widest line to pad other lines
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

// Counts how many valid map lines exist
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

// Copies each line and pads with spaces
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

int	is_in_bounds(t_data *g, int x, int y)
{
	return (x >= 0 && y >= 0 && y < g->height && x < g->width);
}
