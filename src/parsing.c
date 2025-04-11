/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:33 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/11 12:20:51 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// this functions populates the height and width of the game map, but it considers it as always a rectangle ( same case as valid walls )
// using it just for testing.
static int	llen_calc(t_data *game)
{
	int	i;
	int	line_len;

	if (game->map == NULL || game->map[0] == NULL)
		return (2);
	i = 0;
	line_len = ft_strlen(game->map[i]);
	while (game->map[i] != NULL)
	{
		if ((int)ft_strlen(game->map[i]) != line_len)
			return (2);
		i++;
	}
	game->height = i;
	game->width = line_len;
	return (0);
}

static int	extention(char *str)
{
	int	len;

	if (str == NULL)
		return (2);
	len = ft_strlen(str);
	if (len < 4)
		return (2);
	if (str[len - 1] != 'b' || str[len - 2] != 'u'
		|| str[len - 3] != 'c' || str[len - 4] != '.')
		return (2);
	return (0);
}

// problem, it considers the map as always being a rectangle
static int	valid_walls(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->height - 1)
		if (game->map[i][0] == '0')
			return (2);
	i = -1;
	while (++i < game->height - 1)
		if (game->map[i][game->width - 1] == '0')
			return (2);
	i = -1;
	while (++i < game->width - 1)
		if (game->map[0][i] == '0')
			return (2);
	i = -1;
	while (++i < game->width)
		if (game->map[game->height - 1][i] == '0')
			return (2);
	return (0);
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
				game->px = i;
				game->py = j;
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
			if (game->map[i][j] != 'W' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'N' && game->map[i][j] != '0'
				&& game->map[i][j] != '1' && game->map[i][j] != 'S')
				return (2);
	}
	return (0);
}

int	valid_map(char *str, t_data *game)
{
	if (llen_calc(game) == 2)
		return (printf("Error\nnot a valid extension.\n"));
	if (extention(str) == 2)
		return (printf("Error\nnot a valid extension.\n"));
	if (valid_walls(game) == 2)
		return (printf("Error\ninvalid walls.\n"));
	if (has_player(game) == 2)
		return (printf("Error\nmissing Player.\n"));
	if (char_cmp(game) == 2)
		return (printf("Error\nunknown character inside map.\n"));
	free_map(game->map);
	readmap(str, game);
	return (0);
}
