/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:21:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/04/26 16:25:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "minilibx-linux/mlx.h"

// Define constants for game configuration
# define MOVE_SPEED 0.2
# define ROT_SPEED 0.1
# define FOV (M_PI / 2)
# define WIDTH 1920 //1240
# define HEIGHT 1080 //840

// Map defines
# define WALL '1'
# define FLOOR '0'
# define O_DOOR 'd'
# define C_DOOR 'D'

// Pi constants for angle calculations
# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923

// Map-related structs
typedef struct s_map
{
	void	*minimap;
	void	*map;
	int		size_line;
	int		y_offset;
	int		x_offset;
	int		pixel_color;
	int		wall_color;
}	t_map;

// Coordinates struct
typedef struct s_coordinate
{
	double	x;
	double	y;
}	t_coordinate;

// Image struct
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		tex_y;
	int		tex_x;
	int		color;
}	t_image;

// Texture struct
typedef struct s_texture
{
	char	*files[4];
	t_image	images[5];
}	t_texture;

// Color struct
typedef struct s_color
{
	char	*floor;
	char	*ceiling;
	int		f_rgb[3];
	int		c_rgb[3];
	int		f_hex;
	int		c_hex;
}	t_color;

// Ray struct
typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	double	side_dist_y;
	double	side_dist_x;
	double	delta_x;
	double	delta_y;
	double	perp_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		pixel_x;
	int		pixel_y;
	int		*img_data;
}	t_ray;

// Main data struct
typedef struct s_data
{
	void			*window;
	void			*init;
	char			**map;
	char			**file;
	double			px;
	double			py;
	int				player;
	double			player_angle;
	t_coordinate	player_pos;
	int				height;
	int				width;
	t_map			minimap;
	t_ray			ray;
	t_texture		textures;
	t_color			colors;
}	t_data;

/********************* INIT *********************/
void			init_struct_game(t_data *game);
int				close_window(t_data *game);

/********************* ERROR HANDLING *********************/
void			error_handler(t_data *data, char *msg);

/********************* TEXTURE AND COLOR *********************/
int				init_texture_color_names(t_data *data);
unsigned int	rgb_to_hex(int *rgb);
int				has_three_numbers(char *str);
void			save_rgb(t_data *data);
char			*get_info(char *file, int flag);
void			duplicate_texture_or_color(t_data *data);
void			is_valid_textures(t_data *data);
void			is_valid_colors(t_data *data);
void			init_images(t_data *game);
void			draw_ceiling_floor(t_data *game, int draw_start,
					int draw_end, int x);
int				flip_textures(t_image *texture, t_data *game);

/********************* MAP HANDLING *********************/
int				flood_fill(t_data *game, int y, int x);
void			render_minimap(t_data *game);
void			render_map(t_data *game);
int				valid_map(char *str, t_data *game);
int				is_flood_valid(char **map, t_data *g, int x, int y);
char			**extract_map(t_data *game, char **file, int start_y);
int				find_biggest_line(char **file);
int				map_size_valid_char(char **file, int start_y);
char			*get_map_line(char *file_line, int size);
int				count_file_lines(char *file);
void			perform_dda(t_data *game, double ray_angle);
char			**read_file_to_matrix(char *file);
void			fill_recursive(char **map, int y, int x);
char			**duplicate_map(char **src, int height);
int				is_in_bounds(t_data *g, int x, int y);

/********************* MEMORY HANDLING *********************/
void			free_matrix(char **matrix);
void			free_textures(t_texture *textures, void *mlx_ptr);


/********************* PLAYER MOVEMENT *********************/
int				check_quadrant(double player_angle);
void			move_player(int keysym, t_data *game);
void			move_player_up(t_data *game, int quad);
void			move_player_down(t_data *game, int quad);
void			move_player_left(t_data *game, int quad);
void			move_player_right(t_data *game, int quad);

#endif
