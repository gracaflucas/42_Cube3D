/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:51:37 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 12:35:47 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/** @brief Validates and processes ceiling and floor color definitions.
 * This function checks whether the ceiling and floor color strings
 * exist and are correctly formatted as RGB values. It parses them,
 * validates that each component is within the 0–255 range, and then 
 * converts them to hexadecimal format.
 * @param data Pointer to the main game data structure. */
void	is_valid_colors(t_data *data)
{
	int	i;

	i = -1;
	if (!data->colors.ceiling || !data->colors.floor)
		error_handler(data, "Missing color");
	if (!has_three_numbers(data->colors.ceiling)
		|| !has_three_numbers(data->colors.floor))
		error_handler(data, "Invalid color format");
	save_rgb(data);
	while (++i < 3)
		if (data->colors.f_rgb[i] > 255 || data->colors.c_rgb[i] > 255)
			error_handler(data, "Color component > 255");
	data->colors.f_hex = rgb_to_hex(data->colors.f_rgb);
	data->colors.c_hex = rgb_to_hex(data->colors.c_rgb);
}

/** @brief Checks if a string contains exactly three valid numeric
*components separated by commas. Parses a color string to confirm
that it contains three numeric values separated by exactly two
commas, and only contains valid characters (digits, commas, spaces).
 * @param str The input string representing an RGB color (e.g., "255,200,100").
 * @return 1 if the string is valid, 0 otherwise.*/
int	has_three_numbers(char *str)
{
	int		i;
	int		comma_count;
	int		num_count;
	char	*trimmed;

	i = 0;
	comma_count = 0;
	num_count = 0;
	trimmed = ft_strtrim(str, " \n\t");
	while (trimmed[i] != '\0')
	{
		if (trimmed[i] == ',')
			comma_count++;
		else if (ft_isdigit(trimmed[i]))
		{
			num_count += jump(trimmed, &i);
			continue ;
		}
		else if (trimmed[i] == ' ' || trimmed[i] == '\t')
			i++;
		else
			return (free(trimmed), 0);
		i++;
	}
	return (free(trimmed), comma_count == 2 && num_count == 3);
}

/** @brief Parses and stores RGB values for floor and ceiling from 
 * string format. Splits the floor and ceiling color strings by 
 * comma and converts each part to integers, storing them in the
 * `f_rgb` and `c_rgb` arrays in `t_colors`.
 * @param data Pointer to the main game data structure.*/
void	save_rgb(t_data *data)
{
	char	**floor_rgb;
	char	**ceiling_rgb;

	floor_rgb = ft_split(data->colors.floor, ',');
	ceiling_rgb = ft_split(data->colors.ceiling, ',');
	data->colors.f_rgb[0] = ft_atoi(floor_rgb[0]);
	data->colors.f_rgb[1] = ft_atoi(floor_rgb[1]);
	data->colors.f_rgb[2] = ft_atoi(floor_rgb[2]);
	data->colors.c_rgb[0] = ft_atoi(ceiling_rgb[0]);
	data->colors.c_rgb[1] = ft_atoi(ceiling_rgb[1]);
	data->colors.c_rgb[2] = ft_atoi(ceiling_rgb[2]);
	free_matrix(floor_rgb);
	free_matrix(ceiling_rgb);
}

/** @brief Converts an RGB triplet to a hexadecimal color code.
 * Each component is assumed to be in the range 0–255. The red component 
 * is shifted 16 bits, green 8 bits, and blue remains unchanged.
 * @param rgb Pointer to an array of 3 integers representing RGB values.
 * @return An unsigned int containing the hexadecimal representation.*/
unsigned int	rgb_to_hex(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
