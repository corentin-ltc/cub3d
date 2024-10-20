#include "cub3d.h"

int	release_input(int keycode, t_game *game)
{
	if (keycode == 65363) // droite
		game->player->right_pressed = false;
	if (keycode == 65361) // gauche
		game->player->left_pressed = false;
	if (keycode == 65362) // haut
		game->player->up_pressed = false;
	if (keycode == 65364) // bas
		game->player->down_pressed = false;

	return (0);
}

int main(void)
{
	t_mlx_data		mlx_data;
	t_textures		textures;
	t_game			game;
	t_player		player;

	char 		*map[] = {
    					"    1111111111111111111111   ",
    					"1  110000000000000000001111  ",
    					"111110011100W000000011111    ",
    					"  110001 10000001001111111111",
    					"11111111111111111111         "
						};
	// char 		*map[] = {
    // 					"    1111111111  ",
    // 					"1  11000W00001  ",
    // 					"11111111111111    ",
	// 					};
	game.map = map;
	game.player = &player;
	player.position_y = 0;
	player.position_x = 0;
	player.down_pressed = false;
	player.up_pressed = false;
	player.left_pressed = false;
	player.right_pressed = false;
	mlx_data.mlx_ptr = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx_ptr, 1000, 1010, "cub3d");
	if (!mlx_data.mlx_win)
		free_and_exit(&mlx_data, &game);
	init_textures(&mlx_data, &textures, &game);
	mlx_hook(mlx_data.mlx_win, DestroyNotify, 0, exit_game, &game);
	mlx_hook(mlx_data.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(mlx_data.mlx_win, 3, 1L << 1, release_input, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, update, &game);
	mlx_loop(mlx_data.mlx_ptr);
}