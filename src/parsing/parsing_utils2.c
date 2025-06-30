/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:55:41 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/30 11:39:34 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Performs a flood fill from the player's position to
 *  validate map closure.
 * Duplicates the current map and recursively replaces walkable
 *  tiles from
 * the player's position. If any '0' or player-directional 
 * character (N, S, E, W)
 * remains after the fill, the map is not properly enclosed.
 * @param game Pointer to the game state.
 * @param y The player's initial Y coordinate.
 * @param x The player's initial X coordinate.
 * @return 1 if the map is enclosed, 0 if there are leaks.*/
int	flood_fill(t_data *game, int y, int x)
{
	char	c;

	if (y < 0 || y >= game->height || x < 0 || x >= game->width)
		return (0);
	c = game->map_array[y][x];
	if (c == '1' || c == 'O')
		return (1);
	if (c == ' ')
		return (0);
	game->map_array[y][x] = 'O';
	if (!flood_fill(game, y + 1, x))
		return (0);
	if (!flood_fill(game, y - 1, x))
		return (0);
	if (!flood_fill(game, y, x + 1))
		return (0);
	if (!flood_fill(game, y, x - 1))
		return (0);
	return (1);
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

int	parser(t_data *game, char **file)
{
	if (!game->map_array)
		return (error_handler(game, "invalid map layout.", file), 1);
	if (has_player(game) == 2)
		return (error_handler(game, "missing or duplicate player.", file), 1);
	if (char_cmp(game) == 2)
		return (error_handler(game, "unknown character inside map.", file), 1);
	if (!check_border(game->map_array, game->width, game->height))
		return (error_handler(game, "map not enclosed at border.", file), 1);
	if (!flood_fill(game, (int)game->py, (int)game->px))
		return (error_handler(game, "map is not enclosed.", file), 1);
	return (0);
}

/** @brief Extracts and trims information from a configuration line.
 * Skips initial whitespace and a number of characters defined by `flag` 
 * to retrieve a cleaned string (e.g., texture path or color definition).
 * @param file The raw input line from the configuration file.
 * @param flag The number of extra characters to skip 
 * (e.g., 2 for "NO ", 1 for "F ").
 * @return A newly allocated trimmed string with the extracted information.*/
char	*get_info(char *file, int flag)
{
	int		i;
	char	*result;

	i = 0;
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	i += flag;
	result = ft_strtrim(&file[i], " \n\t");
	return (result);
}
