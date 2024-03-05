/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/05 10:59:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/so_long.h"

typedef struct	s_state {
	void	*mlx;
	void	*win;
}				t_state;

int keyhook(int keycode, t_state *vars)
{
	(void)vars;
	printf("The key has been pressed: (%d)\n", keycode);
	return (0);
}

int mousehook(int mousecode)
{
	printf("Mouse event. %d\n", mousecode);
	return (0);
}

int mousemovehook(int x, int y, t_state *vars)
{
	(void)vars;
	printf("Hello! %d %d\n", x, y);
	return (0);
}

void	init_xpm_tiles(t_game *game)
{
	int tile_size;

	tile_size = TILE_SIZE;
	game->tiles.wall = mlx_xpm_file_to_image(game->mlx, WALL_TILE_PATH, &tile_size, &tile_size);
	game->tiles.floor = mlx_xpm_file_to_image(game->mlx, FLOOR_TILE_PATH, &tile_size, &tile_size);
	game->tiles.player_left = mlx_xpm_file_to_image(game->mlx, PLAYER_LEFT_TILE_PATH, &tile_size, &tile_size);
	game->tiles.player_right = mlx_xpm_file_to_image(game->mlx, PLAYER_RIGHT_TILE_PATH, &tile_size, &tile_size);
	game->tiles.player_current = mlx_xpm_file_to_image(game->mlx, PLAYER_RIGHT_TILE_PATH, &tile_size, &tile_size);
	game->tiles.collectible_1 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_1_TILE_PATH, &tile_size, &tile_size);
	game->tiles.collectible_2 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_2_TILE_PATH, &tile_size, &tile_size);
	game->tiles.collectible_3 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_3_TILE_PATH, &tile_size, &tile_size);
	game->tiles.enemy = mlx_xpm_file_to_image(game->mlx, ENEMY_TILE_PATH, &tile_size, &tile_size);
	game->tiles.exit = mlx_xpm_file_to_image(game->mlx, EXIT_TILE_PATH, &tile_size, &tile_size);
}

void	move_player(t_pos new_pos, t_game *game)
{
	char	*player_moves_count_str;

	if (game->map.rows[new_pos.y][new_pos.x] == wall_token)
		return ;
	// TODO: if new_pos == enemy YOU LOSE
	if (new_pos.x < game->map.player_pos.x)
		game->tiles.player_current = game->tiles.player_left;
	else if (new_pos.x > game->map.player_pos.x)
		game->tiles.player_current = game->tiles.player_right;
	mlx_put_image_to_window(game->mlx, game->win, game->tiles.floor, game->map.player_pos.x * TILE_SIZE, game->map.player_pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->win, game->tiles.player_current, new_pos.x * TILE_SIZE, new_pos.y * TILE_SIZE);
	game->map.player_pos.x = new_pos.x;
	game->map.player_pos.y = new_pos.y;
	game->player_moves_count++;
	player_moves_count_str = ft_itoa(game->player_moves_count);
	// TODO: if (!player_moves_count_str) handle memory error
	mlx_string_put(game->mlx, game->win, 15, 15, 0xADD8E6, player_moves_count_str);
	free(player_moves_count_str);
}

int	handle_keyboard_input(int keysym, t_game *game)
{
	ft_printf("%d\n", XK_W);
	ft_printf("%d\n", XK_w);
	if (keysym == XK_Escape)
	{
		// TODO: quit game
	}
	else if (keysym == XK_a || keysym == XK_Left)
		move_player((t_pos){.x=game->map.player_pos.x - 1, .y=game->map.player_pos.y}, game);
	else if (keysym == XK_d || keysym == XK_Right)
		move_player((t_pos){.x=game->map.player_pos.x + 1, .y=game->map.player_pos.y}, game);
	else if (keysym == XK_w || keysym == XK_Up)
		move_player((t_pos){.x=game->map.player_pos.x, .y=game->map.player_pos.y - 1}, game);
	else if (keysym == XK_s || keysym == XK_Down)
		move_player((t_pos){.x=game->map.player_pos.x, .y=game->map.player_pos.y + 1}, game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	parse(argv[1], &game.map);
	game.map.player_pos.y = 3;
	game.map.player_pos.x = 1;

	// init mlx and then clear every variable
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map.x * TILE_SIZE, game.map.y * TILE_SIZE, "so_long");

	// init game.tiles
	// clear everything after
	init_xpm_tiles(&game);

	// render game.tiles
	int i = 0;
	while (game.map.rows[i])
	{
		int j = 0;
		while (game.map.rows[i][j])
		{
			if (game.map.rows[i][j] == wall_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.wall, TILE_SIZE * j, TILE_SIZE * i);
			else if (game.map.rows[i][j] == floor_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.floor, TILE_SIZE * j, TILE_SIZE * i);
			else if (game.map.rows[i][j] == collectible_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.collectible_1, TILE_SIZE * j, TILE_SIZE * i);
			else if (game.map.rows[i][j] == enemy_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.enemy, TILE_SIZE * j, TILE_SIZE * i);
			else if (game.map.rows[i][j] == exit_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.exit, TILE_SIZE * j, TILE_SIZE * i);
			else if (game.map.rows[i][j] == player_token)
				mlx_put_image_to_window(game.mlx, game.win, game.tiles.player_right, TILE_SIZE * j, TILE_SIZE * i);
			j++;
		}
		i++;
	}

	mlx_string_put(game.mlx, game.win, 15, 15, 0xADD8E6, "Hello world");

	// init hooks and loop
	mlx_key_hook(game.win, handle_keyboard_input, &game);
	mlx_loop(game.mlx);
}
// void	*image;
// t_state	state;
// int 	width;
// int 	height;
//
// state.mlx = mlx_init();
// if (!state.mlx)
// 	return (EXIT_FAILURE);
// state.win = mlx_new_window(state.mlx, 600, 400, "Hello world!");
// width = 900;
// height = 900;
// image = mlx_xpm_file_to_image(state.mlx, "./us.xpm", &width, &height);
// mlx_put_image_to_window(state.mlx, state.win, image, 0, 0);
// mlx_loop(state.mlx);
// mlx_destroy_window(state.mlx, state.win);
// mlx_destroy_display(state.mlx);
// free(state.mlx);
