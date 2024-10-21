#include "cub3d.h"

int	release_input(int keycode, t_game *game)
{
	if (keycode == 65363) // droite
		game->controls->right_pressed = false;
	if (keycode == 65361) // gauche
		game->controls->left_pressed = false;
	if (keycode == 65362) // haut
		game->controls->up_pressed = false;
	if (keycode == 65364) // bas
		game->controls->down_pressed = false;

	return (0);
}

int main(void)
{
	t_mlx_data		mlx_data;
	t_textures		textures;
	t_game			game;
	t_player		player;
	t_controls		controls;
	t_img			img;

	char 		*map[] = {
    					"111111111111111111111   ",
    					"11W000000000000000001111  ",
    					"1111100111000000000011111    ",
    					"110001 1000001001111111111",
    					"11111111111111111111         "
						};
	// char 		*map[] = {
    // 					"    1111111111  ",
    // 					"1  11000W00001  ",
    // 					"11111111111111    ",
	// 					};
	//spawnpos = [1][5]

	player.start_x = 2;
	player.start_y = 1;
	game.map = map;
	game.controls = &controls;
	game.player = &player;
	controls.down_pressed = false;
	controls.up_pressed = false;
	controls.left_pressed = false;
	controls.right_pressed = false;
	mlx_data.img = &img;
	init_mlx(&mlx_data);
	init_textures(&mlx_data, &textures, &game);
	mlx_hook(mlx_data.mlx_win, DestroyNotify, 0, exit_game, &game);
	mlx_hook(mlx_data.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(mlx_data.mlx_win, 3, 1L << 1, release_input, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, update, &game);
	mlx_loop(mlx_data.mlx_ptr);
}