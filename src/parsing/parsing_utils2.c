/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:55:41 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/12 12:06:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Performs a flood fill from the player's position to validate map closure.
 * Duplicates the current map and recursively replaces walkable tiles from
 * the player's position. If any '0' or player-directional character (N, S, E, W)
 * remains after the fill, the map is not properly enclosed.
 * @param game Pointer to the game state.
 * @param y The player's initial Y coordinate.
 * @param x The player's initial X coordinate.
 * @return 1 if the map is enclosed, 0 if there are leaks.*/
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

/** @brief Calculates the height of the wall slice to be drawn for a ray
 * Uses the perpendicular distance from the player to the wall (`pd`)
 * to compute `line_height` (scaled to screen height) and sets the
 * unclipped draw start position for vertical line rendering.
 * @param game Pointer to the game state, containing ray data.*/
void	calc_lines(t_data *game)
{
	game->line_height = (int)(HEIGHT / game->ray.pd);
	game->unclipped_start = -game->line_height / 2 + HEIGHT / 2;
}

/** @brief Advances the index over a numeric substring in the string.
 * Used to count complete numbers in a comma-separated RGB string.
 * Advances the given index over all digits in a number.
 * @param trimmed The trimmed string to analyze.
 * @param i Pointer to the index to advance.
 * @return Always returns 1 to signal a number was found.*/
int	jump(char *trimmed, int *i)
{
	while (ft_isdigit(trimmed[*i]))
		(*i)++;
	return (1);
}
