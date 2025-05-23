/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:21:36 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/05/23 13:55:12 by lufiguei         ###   ########.fr       */
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

// Define constants for game configuration
# define MOVE_SPEED 0.2 //How fast the player moves.
# define ROT_SPEED 0.1 //How fast the player rotates.
# define FOV (M_PI / 3) // Field of view, set to 90 degrees (π/2).
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

// Pi constants for angle calculations
# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923

// Map-related structs
typedef struct s_map
{
	void	*minimap;// A pointer to an image representing the minimap
	void	*map;//A pointer to the map image.
	int		size_line;// related to pixel handling and offsets for the minimap display.
	int		y_offset;// related to pixel handling and offsets for the minimap display.
	int		x_offset;// related to pixel handling and offsets for the minimap display.
	int		pixel_color;//Colors for the minimap or map pixels
	int		wall_color;//Colors for the minimap or map pixels
}	t_map;

// Coordinates struct -  used for representing 2D coordinates in the game
typedef struct s_coordinate
{
	double	x;
	double	y;
}	t_coordinate;

// Image struct
typedef struct s_image
{
	void	*img;//A pointer to the actual image.
	char	*addr;// pointer to the image's pixel data (used to access and modify the image).
	int		bits_per_pixel;//Image format information (important for pixel manipulation)
	int		line_len;//Image format information
	int		endian;//Image format information
	int		width; //Dimensions of the image.
	int		height;//Dimensions of the image.
	int		tex_y;//Coordinates to access specific pixels of a texture (for wall rendering).
	int		tex_x;//Coordinates to access specific pixels of a texture
	int		color;//Holds the current pixel color (used for wall rendering).
}	t_image;

// Texture struct
typedef struct s_texture
{
	char	*files[4];//Holds file paths for the four textures used for walls (N, S, E, W).
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
	double	side_dist_y;//The distance to the nearest horizontal and vertical grid lines.
	double	side_dist_x;//The distance to the nearest horizontal and vertical grid lines.
	double	delta_x;//The distances the ray needs to move to cross a cell in the X or Y direction.
	double	delta_y;//The distances the ray needs to move to cross a cell in the X or Y direction.
	double	perp_dist;//The perpendicular distance from the player to the wall (wall height).
	int		step_x;//Directional steps to move the ray (either +1 or -1).
	int		step_y;//Directional steps to move the ray (either +1 or -1).
	int		map_x;//The current map cell the ray is in.
	int		map_y;//The current map cell the ray is in.
	int		hit;//Whether the ray has hit a wall or not.
	int		pixel_x;//Coordinates of the pixel in the image buffer where the ray hit.
	int		pixel_y;//Coordinates of the pixel in the image buffer where the ray hit.
	int		*img_data;//Pixel data to be rendered for the current ray.
}	t_ray;

// Main data struct
typedef struct s_data
{
	void			*window;//Pointer to the window and MLX initialization.
	void			*init;//Pointer to the window and MLX initialization.
	char			**map_array;//A 2D array representing the game map (e.g., walls, floors).
	char			**file;// A 2D array holding data related to the file
	double			px;//player's position on the map.
	double			py;//player's position on the map.
	int				player;//integer flag or identifier for the player.
	double			player_angle;//player's view direction in radians.
	int				height;//Dimensions of the window.
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
void			perform_dda(t_data *game, double ray_angle);
char			**read_file_to_matrix(char *file);
void			fill_recursive(char **map, int y, int x);
char			**duplicate_map(char **src, int height);
int				is_in_bounds(t_data *g, int x, int y);

/********************* MEMORY HANDLING *********************/
void			free_matrix(char **matrix);
void			free_textures(t_texture *textures, void *mlx_ptr);

/********************* PLAYER MOVEMENT *********************/
int				check_quad(double player_angle);
void			move_player(int keysym, t_data *game);
void			move_up(t_data *game, int quad);
void			move_down(t_data *game, int quad);
void			move_left(t_data *game, int quad);
void			move_right(t_data *game, int quad);
void			change_player_position(t_coordinate *new_pos, t_data *game);
void			walk_move(t_data *game);

#endif
