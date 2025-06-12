/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:33 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:01:09 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

static void	get_pa(t_data *game, char c)
{
	if (c == 'N')
		game->pa = -PI_2;
	else if (c == 'S')
		game->pa = PI_2;
	else if (c == 'E')
		game->pa = 0;
	else if (c == 'W')
		game->pa = PI;
}

static int	has_player(t_data *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map_array[++i])
	{
		j = -1;
		while (game->map_array[i][++j])
		{
			if (game->map_array[i][j] == 'W' || game->map_array[i][j] == 'S'
				|| game->map_array[i][j] == 'E' || game->map_array[i][j] == 'N')
			{
				game->px = j + 0.5;
				game->py = i + 0.5;
				get_pa(game, game->map_array[i][j]);
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
	while (game->map_array[++i])
	{
		j = -1;
		while (game->map_array[i][++j])
		{
			if (game->map_array[i][j] == '\n' || game->map_array[i][j] == ' ')
				continue ;
			if (game->map_array[i][j] != 'W' && game->map_array[i][j] != 'E'
				&& game->map_array[i][j] != 'N' && game->map_array[i][j] != '0'
				&& game->map_array[i][j] != '1' && game->map_array[i][j] != 'S')
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
	game->map_array = extract_map(game, file, start_y);
	if (!game->map_array)
		return (error_handler(game, "invalid map layout."), 1);
	if (has_player(game) == 2)
		return (error_handler(game, "missing or duplicate player."), 1);
	if (char_cmp(game) == 2)
		return (error_handler(game, "unknown character inside map."), 1);
	if (!flood_fill(game, (int)game->py, (int)game->px))
		return (error_handler(game, "map is not enclosed."), 1);
	return (0);
}
