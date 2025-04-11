/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:54 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/11 12:37:14 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_double_newline(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
		if (buffer[i] == '\n')
			if (buffer[i + 1] != '\0' && buffer[i + 1] == '\n')
				return (2);
	return (0);
}

static int	loadmap(int fd, char **buffer)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = *buffer;
		*buffer = ft_strjoin(*buffer, line);
		free(tmp);
		free(line);
		if (*buffer == NULL)
		{
			close (fd);
			return (printf("Error\nMemory allocation failed.\n"));
		}
	}
	return (0);
}

int	readmap(char *argv, t_data *game)
{
	int		fd;
	char	*buffer;

	buffer = ft_strdup("");
	if (buffer == NULL)
		return (printf("Error\nMemory allocation failed.\n"));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		return (printf("Error\nCouldnt open file.\n"));
	}
	if (loadmap(fd, &buffer))
	{
		close(fd);
		return (printf("Error\nLoading map failed.\n"));
	}
	close(fd);
	if (is_double_newline(buffer) == 2)
		return (free(buffer), printf("Error\nmap contains empty line.\n"));
	game->map = ft_split(buffer, '\n');
	free(buffer);
	if (game->map == NULL)
		return (printf("Error\nMap Split failed.\n"));
	return (0);
}

// a simple render for testing the ray in 2D
// how to fix the size of player in comparison with the whole map?
// how to walk in the map only slighly, not the whole block?
void	render_map(t_data *game)
{
	int *img_data;
	int x_offset, y_offset, bpp, size_line, endian, color, i, j;

	if (!game->map_img)
		game->map_img = mlx_new_image(game->init, game->width * 139, game->height * 139);
	img_data = (int*)mlx_get_data_addr(game->map_img, &bpp, &size_line, &endian);
	for (i = 0; i < game->height; i++)
	{
		for (j = 0; j < game->width; j++)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
				color = 0xFFFF00;
			else if (game->map[i][j] == '0')
				color = 0x000000;
			else if (game->map[i][j] == '1')
				color = 0xFFFFFF;
			x_offset = j * 139;
			y_offset = i * 139;
			for (int y = 0; y < 135; y++)
				for (int x = 0; x < 135; x++)
					img_data[(y_offset + y) * (size_line / 4) + (x_offset + x)] = color;
		}
	}
	mlx_put_image_to_window(game->init, game->window, game->map_img, 0, 0);
}

int	update_map(t_data *game, int x, int y)
{
	int			old_x;
	int			old_y;

	old_x = game->px;
	old_y = game->py;
	game->px = x;
	game->py = y;
	game->map[x][y] = game->player_angle;
	game->map[old_x][old_y] = '0';
	render_map(game);
	return (1);
}
