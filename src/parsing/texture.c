/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:51:37 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/18 20:25:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/* GET BACK TO THIS ONCE WE HAVE THE TEXTURES
 int	init_texture_color_names(t_data *data)
{
	int		i = -1;
	char	**file = data->file;

	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") && !data->textures.files[0])
			data->textures.files[0] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "EA ") && !data->textures.files[1])
			data->textures.files[1] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "SO ") && !data->textures.files[2])
			data->textures.files[2] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "WE ") && !data->textures.files[3])
			data->textures.files[3] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "F ") && !data->colors.floor)
			data->colors.floor = get_info(file[i], 1);
		else if (ft_strstr(file[i], "C ") && !data->colors.ceiling)
			data->colors.ceiling = get_info(file[i], 1);

		if (data->textures.files[0] && data->textures.files[1]
			&& data->textures.files[2] && data->textures.files[3]
			&& data->colors.floor && data->colors.ceiling)
			return (++i);
	}
	return (0);
} */

int file_exists(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

int	init_texture_color_names(t_data *data)
{
	if (!file_exists(data->textures.files[0]))
	{
		printf("Warning: North texture file not found, using default.\n");
		data->textures.files[0] = NULL;
	}
	if (!file_exists(data->textures.files[1])) {
		printf("Warning: South texture file not found, using default.\n");
		data->textures.files[1] = NULL;
	}
	if (!file_exists(data->textures.files[2])) {
		printf("Warning: East texture file not found, using default.\n");
		data->textures.files[2] = NULL;
	}
	if (!file_exists(data->textures.files[3])) {
		printf("Warning: West texture file not found, using default.\n");
		data->textures.files[3] = NULL;
	}
	return (1);
}

void	duplicate_texture_or_color(t_data *data)
{
	char	**file = data->file;
	int		i = -1;
	int		j;

	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") || ft_strstr(file[i], "SO ")
			|| ft_strstr(file[i], "EA ") || ft_strstr(file[i], "WE ")
			|| ft_strstr(file[i], "F ") || ft_strstr(file[i], "C "))
		{
			j = i;
			while (file[++j])
				if ((ft_strstr(file[i], "NO ") && ft_strstr(file[j], "NO "))
					|| (ft_strstr(file[i], "SO ") && ft_strstr(file[j], "SO "))
					|| (ft_strstr(file[i], "EA ") && ft_strstr(file[j], "EA "))
					|| (ft_strstr(file[i], "WE ") && ft_strstr(file[j], "WE "))
					|| (ft_strstr(file[i], "F ") && ft_strstr(file[j], "F "))
					|| (ft_strstr(file[i], "C ") && ft_strstr(file[j], "C ")))
					error_handler(data, "Duplicate texture or color");
		}
	}
}

void	is_valid_textures(t_data *data)
{
	int	fd;

	if (!data->textures.files[0] || !data->textures.files[1]
		|| !data->textures.files[2] || !data->textures.files[3])
		error_handler(data, "Missing texture");

	for (int i = 0; i < 4; i++)
	{
		fd = open(data->textures.files[i], O_RDONLY);
		if (fd < 0)
			error_handler(data, "Invalid texture file");
		close(fd);
	}
}

void	is_valid_colors(t_data *data)
{
	if (!data->colors.ceiling || !data->colors.floor)
		error_handler(data, "Missing color");

	if (!has_three_numbers(data->colors.ceiling)
		|| !has_three_numbers(data->colors.floor))
		error_handler(data, "Invalid color format");

	save_rgb(data); // fills f_rgb/c_rgb arrays

	for (int i = 0; i < 3; i++)
		if (data->colors.f_rgb[i] > 255 || data->colors.c_rgb[i] > 255)
			error_handler(data, "Color component > 255");

	data->colors.f_hex = rgb_to_hex(data->colors.f_rgb);
	data->colors.c_hex = rgb_to_hex(data->colors.c_rgb);
}

int has_three_numbers(char *str)
{
    int i = 0;
    int comma_count = 0;
    int num_count = 0;

    str = ft_strtrim(str, " \n\t");

    while (str[i] != '\0')
    {
        if (str[i] == ',')
            comma_count++;
        else if (ft_isdigit(str[i]))
        {
            while (ft_isdigit(str[i]))
                i++;
            num_count++;
        }
        else
        {
            return 0;
        }
        i++;
    }

    return (comma_count == 2 && num_count == 3);
}

void save_rgb(t_data *data)
{
    char **floor_rgb = ft_split(data->colors.floor, ',');
    char **ceiling_rgb = ft_split(data->colors.ceiling, ',');

    data->colors.f_rgb[0] = ft_atoi(floor_rgb[0]);
    data->colors.f_rgb[1] = ft_atoi(floor_rgb[1]);
    data->colors.f_rgb[2] = ft_atoi(floor_rgb[2]);

    data->colors.c_rgb[0] = ft_atoi(ceiling_rgb[0]);
    data->colors.c_rgb[1] = ft_atoi(ceiling_rgb[1]);
    data->colors.c_rgb[2] = ft_atoi(ceiling_rgb[2]);

    free_matrix(floor_rgb);
    free_matrix(ceiling_rgb);
}

unsigned int rgb_to_hex(int *rgb)
{
    return (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}