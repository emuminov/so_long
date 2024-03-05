/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/05 16:22:24 by emuminov         ###   ########.fr       */
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
	game->tiles.player_current = game->tiles.player_right;
	game->tiles.collectible_1 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_1_TILE_PATH, &tile_size, &tile_size);
	game->tiles.collectible_2 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_2_TILE_PATH, &tile_size, &tile_size);
	game->tiles.collectible_3 = mlx_xpm_file_to_image(game->mlx, COLLECTIBLE_3_TILE_PATH, &tile_size, &tile_size);
	game->tiles.enemy = mlx_xpm_file_to_image(game->mlx, ENEMY_TILE_PATH, &tile_size, &tile_size);
	game->tiles.exit = mlx_xpm_file_to_image(game->mlx, EXIT_TILE_PATH, &tile_size, &tile_size);
}

void	put_tile_to_pos(t_game *game, void *tile, t_pos pos)
{
		mlx_put_image_to_window(game->mlx, game->win,
		tile, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
}

void	end_game(char *msg, t_game *game)
{
	mlx_destroy_image(game->mlx, game->tiles.wall);
	mlx_destroy_image(game->mlx, game->tiles.exit);
	mlx_destroy_image(game->mlx, game->tiles.enemy);
	mlx_destroy_image(game->mlx, game->tiles.floor);
	mlx_destroy_image(game->mlx, game->tiles.player_left);
	mlx_destroy_image(game->mlx, game->tiles.player_right);
	mlx_destroy_image(game->mlx, game->tiles.collectible_1);
	mlx_destroy_image(game->mlx, game->tiles.collectible_2);
	mlx_destroy_image(game->mlx, game->tiles.collectible_3);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free_split(game->map.rows);
	if (msg)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	move_player(t_pos new_pos, t_game *game)
{
	char	*player_moves_count_str;

	if (game->map.rows[new_pos.y][new_pos.x] == wall_token)
		return ;
	else if (game->map.rows[new_pos.y][new_pos.x] == collectible_token)
	{
		game->map.rows[new_pos.y][new_pos.x] = floor_token;
		game->collected_count++;
	}
	else if (game->map.rows[new_pos.y][new_pos.x] == enemy_token)
		end_game("You lost!\n", game);
	else if (game->map.rows[new_pos.y][new_pos.x] == exit_token && game->collected_count == game->token_count.collectible_count)
		end_game("You won!\n", game);
	if (new_pos.x < game->map.player_pos.x)
		game->tiles.player_current = game->tiles.player_left;
	else if (new_pos.x > game->map.player_pos.x)
		game->tiles.player_current = game->tiles.player_right;
	if (game->map.rows[game->map.player_pos.y][game->map.player_pos.x] == exit_token)
		put_tile_to_pos(game, game->tiles.exit, game->map.player_pos);
	else
		put_tile_to_pos(game, game->tiles.floor, game->map.player_pos);
	put_tile_to_pos(game, game->tiles.player_current, new_pos);
	game->map.player_pos = new_pos;
	game->player_moves_count++;
	player_moves_count_str = ft_itoa(game->player_moves_count);
	// TODO: if (!player_moves_count_str) handle memory error
	put_tile_to_pos(game, game->tiles.wall, (t_pos){.x=0, .y=0});
	put_tile_to_pos(game, game->tiles.wall, (t_pos){.x=1, .y=0});
	mlx_string_put(game->mlx, game->win, TILE_SIZE / 2, TILE_SIZE / 2, 0xADD8E6, player_moves_count_str);
	free(player_moves_count_str);
}

int	handle_keyboard_input(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		end_game(NULL, game);
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

void	render_initial_graphic(t_game *game)
{
	int y = 0;
	while (game->map.rows[y])
	{
		int x = 0;
		while (game->map.rows[y][x])
		{
			if (game->map.rows[y][x] == wall_token)
				put_tile_to_pos(game, game->tiles.wall, (t_pos){.x=x, .y=y});
			else if (game->map.rows[y][x] == floor_token)
				put_tile_to_pos(game, game->tiles.floor, (t_pos){.x=x, .y=y});
			else if (game->map.rows[y][x] == collectible_token)
				put_tile_to_pos(game, game->tiles.collectible_1, (t_pos){.x=x, .y=y});
			else if (game->map.rows[y][x] == enemy_token)
				put_tile_to_pos(game, game->tiles.enemy, (t_pos){.x=x, .y=y});
			else if (game->map.rows[y][x] == exit_token)
				put_tile_to_pos(game, game->tiles.exit, (t_pos){.x=x, .y=y});
			else if (game->map.rows[y][x] == player_token)
				put_tile_to_pos(game, game->tiles.player_right, (t_pos){.x=x, .y=y});
			x++;
		}
		y++;
	}
	mlx_string_put(game->mlx, game->win, TILE_SIZE / 2, TILE_SIZE / 2, 0xADD8E6, "0");
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	parse(argv[1], &game);
	game.map.player_pos.y = 3;
	game.map.player_pos.x = 1;

	// init mlx and then clear every variable
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.map.x * TILE_SIZE, game.map.y * TILE_SIZE, "so_long");

	// init game.tiles
	// clear everything after
	init_xpm_tiles(&game);

	// render game.tiles
	render_initial_graphic(&game);

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
// free(state.mlx);
