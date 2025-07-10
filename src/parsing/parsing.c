/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:33 by lufiguei          #+#    #+#             */
/*   Updated: 2025/06/18 11:42:57 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Validates the file extension of the map file.
 * Checks whether the filename ends with ".cub". Returns 0 if valid,
 * otherwise returns 1 for an invalid extension.
 * @param str The map filename.
 * @return 0 if extension is ".cub", 1 otherwise.*/
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

/** @brief Sets the player's initial angle based on direction.
 * Updates the `game->pa` (player angle) based on the character
 * indicating the direction in the map.
 * @param game Pointer to game state.
 * @param c Character representing the player's facing direction 
 * (N, S, E, W).*/
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

/** @brief Checks for player existence and sets position and direction.
 * Searches the map array for the player start character (N, S, E, W),
 * and sets the player's position and direction accordingly.
 * @param game Pointer to game state.
 * @return 0 if one player is found, 2 if none or more than one.*/
int	has_player(t_data *game)
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

/** @brief Validates that all characters in the map are allowed.
 * Allowed characters are: '0', '1', 'N', 'S', 'E', 'W', space, 
 * and newline.
 * @param game Pointer to game state.
 * @return 0 if valid, 2 if invalid characters are found.*/
int	char_cmp(t_data *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map_array[++i])
	{
		j = -1;
		while (game->map_array[i][++j])
		{
			if (game->map_array[i][j] == ' ')
				continue ;
			if (game->map_array[i][j] != 'W' && game->map_array[i][j] != 'E'
				&& game->map_array[i][j] != 'N' && game->map_array[i][j] != 'S'
				&& game->map_array[i][j] != '0' && game->map_array[i][j] != '1')
				return (2);
		}
	}
	return (0);
}

/** @brief Performs full validation of the map file and its contents.
 * This includes:
 * - File extension check
 * - Reading the file into memory
 * - Texture and color parsing
 * - Texture/color duplication checks
 * - RGB value parsing
 * - Extracting map layout
 * - Ensuring a single player is present
 * - Validating allowed characters
 * - Running flood fill to ensure the map is enclosed
 * If any step fails, an appropriate error is thrown and the program exits.
 * @param str Path to the `.cub` map file.
 * @param game Pointer to game state.
 * @return 0 if successful, 1 on failure.*/
int	valid_map(char *str, t_data *game)
{
	char	**file;
	int		start_y;

	file = read_file_to_matrix(str);
	if (!file)
		return (error_handler(game, "map file could not be read."), 1);
	game->file = file;
	if (extention(str))
		return (free_matrix(file),
			error_handler(game, "not a valid extension."), 1);
	start_y = init_texture_color_names(game);
	if (!start_y)
		return (free_matrix(file),
			error_handler(game, "missing texture or color."), 1);
	duplicate_texture_or_color(game);
	is_valid_textures(game, file);
	is_valid_colors(game, file);
	game->map_array = extract_map(game, file, start_y);
	if (parser(game, file) != 0)
		return (1);
	return (0);
}
