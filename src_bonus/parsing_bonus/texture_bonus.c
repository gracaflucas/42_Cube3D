/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:51:37 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/12 11:59:50 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

unsigned int	rgb_to_hex(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
