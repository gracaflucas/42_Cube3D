/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:55:41 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 11:34:53 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	flood_fill(t_data *game, int y, int x)
{
	char	**copy;
	int		i;

	copy = duplicate_map(game->map_array, game->height);
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

void	calc_lines(t_data *game)
{
	game->line_height = (int)(HEIGHT / game->ray.pd);
	game->unclipped_start = -game->line_height / 2 + HEIGHT / 2;
}

int	jump(char *trimmed, int *i)
{
	while (ft_isdigit(trimmed[*i]))
		(*i)++;
	return (1);
}
