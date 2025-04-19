/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:54 by lufiguei          #+#    #+#             */
/*   Updated: 2025/04/18 18:53:40 by ana-lda-         ###   ########.fr       */
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
