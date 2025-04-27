/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:33 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/27 15:26:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// What We Need to Adapt:

//     Load the .cub file line by line and store it in a matrix (2D char**).

//     Validate the extension .cub before doing anything.

//     Treat irregular maps (not strictly rectangles) without crashing.

//     Ensure the map is properly closed (walls check).

//     Extract and validate the player position (just one allowed).

static int	extention(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (len < 4)
		return (1);
	if (str[len - 1] != 'b')
		return (1);
	if (str[len - 2] != 'u')
		return (1);
	if (str[len - 3] != 'c')
		return (1);
	if (str[len - 4] != '.')
		return (1);
	return (0);
}

static void get_player_angle(t_data *game, char c)
{
	if (c == 'N')
		game->player_angle = -PI_2;
	else if (c == 'S')
		game->player_angle = PI_2;
	else if (c == 'E')
		game->player_angle = 0;
	else if (c == 'W')
		game->player_angle = PI;
}

static int	has_player(t_data *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'W' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'N')
			{
				game->px = j + 0.5;
				game->py = i + 0.5;
				get_player_angle(game, game->map[i][j]);
				game->player += 1;
			}
		}
	}
	if (game->player != 1)
		return (2);
	return (0);
}

static int	char_cmp(t_data *game)
{
	int		i;
	int		j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '\n' || game->map[i][j] == ' ')
				continue ;
			if (game->map[i][j] != 'W' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'N' && game->map[i][j] != '0'
				&& game->map[i][j] != '1' && game->map[i][j] != 'S')
				return (2);
		}
	}
	return (0);
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

int	valid_map(char *str, t_data *game)
{
	char	**file;
	int		start_y;

	file = read_file_to_matrix(str);
	if (!file)
		return (error_handler(game, "map file could not be read."), 1);
	game->file = file;
	if (extention(str) == 2)
		return (error_handler(game, "not a valid extension."), 1);
	start_y = init_texture_color_names(game);
	if (!start_y)
		return (error_handler(game, "missing texture or color."), 1);
	duplicate_texture_or_color(game);
	is_valid_textures(game);
	is_valid_colors(game);
	game->map = extract_map(game, file, start_y);
	if (!game->map)
		return (error_handler(game, "invalid map layout."), 1);
	if (has_player(game) == 2)
		return (error_handler(game, "missing or duplicate player."), 1);
	if (char_cmp(game) == 2)
		return (error_handler(game, "unknown character inside map."), 1);
	// if (!flood_fill(game, (int)game->px, (int)game->py))
	// 	return (error_handler(game, "map is not enclosed."), 1);
	return (0);
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

int	flood_fill(t_data *game, int y, int x)
{
	char	**copy;
	int		i;

	copy = duplicate_map(game->map, game->height);
	if (!copy)
		return (0);
	fill_recursive(copy, y, x);
	i = -1;
	while (++i < game->height)
	{
		if (ft_strchr(copy[i], '0') || ft_strchr(copy[i], 'N')
			|| ft_strchr(copy[i], 'S') || ft_strchr(copy[i], 'E')	
			|| ft_strchr(copy[i], 'W'))
		{
			free_matrix(copy);
			return (0);
		}
	}
	free_matrix(copy);
	return (1);
}