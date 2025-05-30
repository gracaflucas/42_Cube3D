/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:33 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/30 12:28:33 by lufiguei         ###   ########.fr       */
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

static void	get_player_angle(t_data *game, char c)
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
			return (free_matrix(copy), 0);
	}
	return (free_matrix(copy), 1);
}
