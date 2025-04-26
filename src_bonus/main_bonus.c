#include "cub3D_bonus.h"

static int	is_valid_move(t_data *game, double x, double y)
{
	int mx;
	int my;

	mx = (int)x;
	my = (int)y;
	if (game->map[my][mx] == '1')
		return (0);
	game->px = x;
	game->py = y;
	return (1);
}

static int mouse_move_hook(int x, int y, t_data *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	game->player_angle += delta_x * 0.00009;
	render_map(game);
	render_minimap(game);
	return (0);
}

static void interact_door(t_data *game)
{
    double  interact_distance;
    int  mx;
    int  my;

    interact_distance = 0.5;
    mx = (int)(game->px + cos(game->player_angle) * interact_distance);
    my = (int)(game->py + sin(game->player_angle) * interact_distance);
    if (game->map[mx][my] == 'D')
        game->map[mx][my] = 'd';
    else if (game->map[mx][my] == 'd')
        game->map[mx][my] = 'D';
}

static int	key_hook(int keysym, t_data *game)
{
	double	new_px;
	double	new_py;

	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		game->player_angle -= ROT_SPEED;
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		game->player_angle += ROT_SPEED;
	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
	{
		new_px = game->px + cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py + sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
	{
		new_px = game->px - cos(game->player_angle) * MOVE_SPEED;
		new_py = game->py - sin(game->player_angle) * MOVE_SPEED;
		is_valid_move(game, new_px, new_py);
	}
	if (keysym == XK_E || keysym == XK_e || keysym == XK_space)
		interact_door(game);
	return (render_map(game), render_minimap(game), 0);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (printf("Usage: ./cub3d <map.cub>\n"));
	init_struct_game(&game);
	if (valid_map(argv[1], &game))
		return (free_matrix(game.map), 1);
	game.init = mlx_init();
	if (!game.init)
		return (printf("Error\nInitialization failed.\n"), 1);
	game.window = mlx_new_window(game.init, 1920, 1080, "cub3D");
	if (!game.window)
		return (mlx_destroy_display(game.init), free(game.init),
			printf("Error\nWindow creation failed.\n"), 1);
	render_minimap(&game);
	render_map(&game);
	mlx_key_hook(game.window, &key_hook, &game);
	mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
    mlx_hook(game.window, MotionNotify, PointerMotionMask, mouse_move_hook, &game);
	mlx_loop(game.init);
	return (free_matrix(game.map), 0);
}
