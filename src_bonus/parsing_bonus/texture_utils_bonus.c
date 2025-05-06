/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:26:25 by lufiguei          #+#    #+#             */
/*   Updated: 2025/05/06 11:46:53 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

int	init_texture_color_names(t_data *data)
{
	int		i;
	char	**file;

	i = -1;
	file = data->file;
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
}

int	file_exists(char *filename)
{
	FILE	*file;

	if (!filename)
		return (0);
	file = fopen(filename, "r");
	if (file)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

void	duplicate_texture_or_color(t_data *data)
{
	char	**file;
	int		i;
	int		j;

	i = -1;
	file = data->file;
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

	duplicate_texture_or_color(data);
	if (!data->textures.files[0] || !data->textures.files[1]
		|| !data->textures.files[2] || !data->textures.files[3])
		return (error_handler(data, "No texture found"));
	fd = open(data->textures.files[0], O_RDONLY);
	if (fd < 0)
		return (error_handler(data, "North texture is invalid"));
	fd = open(data->textures.files[1], O_RDONLY);
	if (fd < 0)
		return (error_handler(data, "East texture is invalid"));
	fd = open(data->textures.files[2], O_RDONLY);
	if (fd < 0)
		return (error_handler(data, "South texture is invalid"));
	fd = open(data->textures.files[3], O_RDONLY);
	if (fd < 0)
		return (error_handler(data, "West texture is invalid"));
	return ;
}
