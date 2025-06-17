/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:21:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/06/17 13:31:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "minilibx-linux/mlx.h"

// Pi constants for angle calculations
# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923

// Define constants for game configuration
# define MOVE_SPEED 0.2 //How fast the player moves.
# define ROT_SPEED 0.1 //How fast the player rotates.
# define FOV 1.0471975512 // Approximate value of PI/3
# define WIDTH 1920 //1240 -Resolution of the window.
# define HEIGHT 1080 //840 -Resolution of the window.

// Map defines
# define WALL '1'
# define FLOOR '0'
# define O_DOOR 'd'
# define C_DOOR 'D'

// KEY DEFINES
# define KEY_W XK_w
# define KEY_A XK_a
# define KEY_S XK_s
# define KEY_D XK_d

// Map-related structs
typedef struct s_map
{
	void	*minimap;//A pointer to an image representing the minimap
	void	*map;//A pointer to the map image.
	int		size_line;//related to pixel handling and offsets for minimap
	int		y_offset;//related to pixel handling and offsets for minimap
	int		x_offset;//related to pixel handling and offsets for minimap
	int		pixel_color;//Colors for the minimap or map pixels
	int		wall_color;//Colors for the minimap or map pixels
}	t_map;

// Coordinates struct -used for representing 2D coordinates in the game
typedef struct s_coordinate
{
	double	x;
	double	y;
}	t_coordinate;

// Image struct
typedef struct s_image
{
	void	*img;//A pointer to the actual image.
	char	*addr;//pointer to the image's pixel data
	int		bpp;//Image format information (important for pixel manipulation)
	int		llen;//Image format information
	int		endian;//Image format information
	int		width; //Dimensions of the image.
	int		height;//Dimensions of the image.
	int		tex_y;//to access specific pixels of a texture (wall rendering).
	int		tex_x;//Coordinates to access specific pixels of a texture
	int		color;//Holds the current pixel color (used for wall rendering).
}	t_image;

// Texture struct
typedef struct s_texture
{
	char	*files[4];//Holds file paths for the four textures for walls
	t_image	images[5];//Holds the actual loaded textures
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
	double	x;//The ray's starting position.
	double	y;//The ray's starting position.
	double	angle;//ray's direction/angle.
	double	sy;//The distance to the nearest horizontal and vertical lines.
	double	sx;//The distance to the nearest horizontal and verticallines.
	double	dx;//dist. the ray needs to move to cross a cell in the X or Y dir.
	double	dy;//dist. the ray needs to move to cross a cell in the X or Y dir.
	double	pd;//perpendicular distance from the player to the wall
	int		step_x;//Directional steps to move the ray (either +1 or -1).
	int		step_y;//Directional steps to move the ray (either +1 or -1).
	int		mx;//The current map cell the ray is in.
	int		my;//The current map cell the ray is in.
	int		hit;//Whether the ray has hit a wall or not.
	int		pixel_x;//Coord. of pixel in the image buffer where the ray hit.
	int		pixel_y;//Coord. of pixel in the image buffer where the ray hit.
	int		*img_data;//Pixel data to be rendered for the current ray.
}	t_ray;

// Main data struct
typedef struct s_data
{
	void			*window;//Pointer to the window and MLX initialization.
	void			*init;//Pointer to the window and MLX initialization.
	char			**map_array;//2D array representing game map(walls/floors).
	char			**file;// A 2D array holding data related to the file
	double			px;//player's position on the map.
	double			py;//player's position on the map.
	int				player;//integer flag or identifier for the player.
	double			pa;//player's view direction in radians.
	int				height;//Dimensions of the window.
	int				line_height;
	int				unclipped_start;
	int				movement;
	int				width;//Dimensions of the window.
	t_map			minimap;//minimap data.
	t_map			map;// main map data
	t_ray			ray;//Raycasting data.
	t_texture		textures;//Textures for the walls.
	t_coordinate	player_pos;
	t_color			colors;//Floor and ceiling colors.
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
void			calc_lines(t_data *game);
int				jump(char *trimmed, int *i);

/********************* MAP HANDLING *********************/
int				flood_fill(t_data *game, int y, int x);
void			render_map(t_data *game);
int				valid_map(char *str, t_data *game);
int				is_flood_valid(char **map, t_data *g, int x, int y);
char			**extract_map(t_data *game, char **file, int start_y);
int				find_biggest_line(char **file);
int				map_size_valid_char(char **file, int start_y);
char			*get_map_line(char *file_line, int size);
int				count_file_lines(char *file);
void			perform_dda(t_data *g, double ray_angle);
char			**read_file_to_matrix(char *file);
void			fill_recursive(char **map, int y, int x);
char			**duplicate_map(char **src, int height);
int				is_in_bounds(t_data *g, int x, int y);

/********************* MEMORY HANDLING *********************/
void			free_matrix(char **matrix);
void			free_textures(t_texture *textures, void *mlx_ptr);

/********************* PLAYER MOVEMENT *********************/
int				key_hook(int keysym, t_data *game);
int				is_valid_move(t_data *game, double new_x, double new_y);

#endif