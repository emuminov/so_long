/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/06 14:54:33 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdio.h>

void	put_tile_to_pos(t_game *g, void *tile, t_pos pos)
{
	mlx_put_image_to_window(g->mlx, g->win, tile, pos.x * TILE_SIZE, pos.y
		* TILE_SIZE);
}

void	end_game(int error, char *msg, t_game *g)
{
	mlx_destroy_image(g->mlx, g->tiles.wall);
	mlx_destroy_image(g->mlx, g->tiles.exit);
	mlx_destroy_image(g->mlx, g->tiles.enemy);
	mlx_destroy_image(g->mlx, g->tiles.floor);
	mlx_destroy_image(g->mlx, g->tiles.player_left);
	mlx_destroy_image(g->mlx, g->tiles.player_right);
	mlx_destroy_image(g->mlx, g->tiles.collectible_1);
	mlx_destroy_image(g->mlx, g->tiles.collectible_2);
	mlx_destroy_image(g->mlx, g->tiles.collectible_3);
	if (g->win)
		mlx_destroy_display(g->mlx);
	if (g->mlx)
		mlx_destroy_window(g->mlx, g->win);
	free(g->mlx);
	free(g->map.collectibles_pos);
	ft_free_split(g->map.rows);
	if (msg && !error)
		ft_putstr_fd(msg, STDOUT_FILENO);
	else if (msg && error)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	check_xmp_tiles(t_game *g)
{
	if (!g->tiles.wall || !g->tiles.floor || !g->tiles.player_left
		|| !g->tiles.player_right || !g->tiles.collectible_1
		|| !g->tiles.collectible_2 || !g->tiles.collectible_3 || !g->tiles.enemy
		|| !g->tiles.exit)
		end_game(1, "Memory error\n", g);
}

void	init_xpm_tiles(t_game *g)
{
	int	tile_size;

	tile_size = TILE_SIZE;
	g->tiles.wall = mlx_xpm_file_to_image(g->mlx, WALL_TILE_PATH, &tile_size,
			&tile_size);
	g->tiles.floor = mlx_xpm_file_to_image(g->mlx, FLOOR_TILE_PATH, &tile_size,
			&tile_size);
	g->tiles.player_left = mlx_xpm_file_to_image(g->mlx, PLAYER_LEFT_TILE_PATH,
			&tile_size, &tile_size);
	g->tiles.player_right = mlx_xpm_file_to_image(g->mlx,
			PLAYER_RIGHT_TILE_PATH, &tile_size, &tile_size);
	g->tiles.player_current = g->tiles.player_right;
	g->tiles.collectible_1 = mlx_xpm_file_to_image(g->mlx,
			COLLECTIBLE_1_TILE_PATH, &tile_size, &tile_size);
	g->tiles.collectible_2 = mlx_xpm_file_to_image(g->mlx,
			COLLECTIBLE_2_TILE_PATH, &tile_size, &tile_size);
	g->tiles.collectible_3 = mlx_xpm_file_to_image(g->mlx,
			COLLECTIBLE_3_TILE_PATH, &tile_size, &tile_size);
	g->tiles.enemy = mlx_xpm_file_to_image(g->mlx, ENEMY_TILE_PATH, &tile_size,
			&tile_size);
	g->tiles.exit = mlx_xpm_file_to_image(g->mlx, EXIT_TILE_PATH, &tile_size,
			&tile_size);
}

void	move_player(t_pos new_pos, t_game *g)
{
	char	*player_moves_count_str;

	if (g->map.rows[new_pos.y][new_pos.x] == wall_token)
		return ;
	else if (g->map.rows[new_pos.y][new_pos.x] == collectible_token)
	{
		g->map.rows[new_pos.y][new_pos.x] = floor_token;
		g->collected_count++;
	}
	else if (g->map.rows[new_pos.y][new_pos.x] == enemy_token)
		end_game(0, "You lost!\n", g);
	else if (g->map.rows[new_pos.y][new_pos.x] == exit_token
		&& g->collected_count == g->token_count.collectible_count)
		end_game(0, "You won!\n", g);
	if (new_pos.x < g->map.player_pos.x)
		g->tiles.player_current = g->tiles.player_left;
	else if (new_pos.x > g->map.player_pos.x)
		g->tiles.player_current = g->tiles.player_right;
	if (g->map.rows[g->map.player_pos.y][g->map.player_pos.x] == exit_token)
		put_tile_to_pos(g, g->tiles.exit, g->map.player_pos);
	else
		put_tile_to_pos(g, g->tiles.floor, g->map.player_pos);
	put_tile_to_pos(g, g->tiles.player_current, new_pos);
	g->map.player_pos = new_pos;
	g->player_moves_count++;
	player_moves_count_str = ft_itoa(g->player_moves_count);
	// TODO: if (!player_moves_count_str) handle memory error
	put_tile_to_pos(g, g->tiles.wall, (t_pos){.x = 0, .y = 0});
	put_tile_to_pos(g, g->tiles.wall, (t_pos){.x = 1, .y = 0});
	mlx_string_put(g->mlx, g->win, TILE_SIZE / 2, TILE_SIZE / 2, 0xADD8E6,
		player_moves_count_str);
	free(player_moves_count_str);
}

int	handle_keyboard_input(int keysym, t_game *g)
{
	if (keysym == XK_Escape)
		end_game(0, NULL, g);
	else if (keysym == XK_a || keysym == XK_Left)
		move_player((t_pos){.x = g->map.player_pos.x - 1,
			.y = g->map.player_pos.y}, g);
	else if (keysym == XK_d || keysym == XK_Right)
		move_player((t_pos){.x = g->map.player_pos.x + 1,
			.y = g->map.player_pos.y}, g);
	else if (keysym == XK_w || keysym == XK_Up)
		move_player((t_pos){.x = g->map.player_pos.x, .y = g->map.player_pos.y
			- 1}, g);
	else if (keysym == XK_s || keysym == XK_Down)
		move_player((t_pos){.x = g->map.player_pos.x, .y = g->map.player_pos.y
			+ 1}, g);
	return (0);
}

void	render_initial_graphic(t_game *g)
{
	t_pos	pos;

	pos.y = 0;
	while (g->map.rows[pos.y])
	{
		pos.x = 0;
		while (g->map.rows[pos.y][pos.x])
		{
			if (g->map.rows[pos.y][pos.x] == wall_token)
				put_tile_to_pos(g, g->tiles.wall, pos);
			else if (g->map.rows[pos.y][pos.x] == floor_token)
				put_tile_to_pos(g, g->tiles.floor, pos);
			else if (g->map.rows[pos.y][pos.x] == collectible_token)
				put_tile_to_pos(g, g->tiles.collectible_1, pos);
			else if (g->map.rows[pos.y][pos.x] == enemy_token)
				put_tile_to_pos(g, g->tiles.enemy, pos);
			else if (g->map.rows[pos.y][pos.x] == exit_token)
				put_tile_to_pos(g, g->tiles.exit, pos);
			else if (g->map.rows[pos.y][pos.x] == player_token)
				put_tile_to_pos(g, g->tiles.player_right, pos);
			pos.x++;
		}
		pos.y++;
	}
	mlx_string_put(g->mlx, g->win, TILE_SIZE / 2, TILE_SIZE / 2, 0xADD8E6, "0");
}

void	animate_beer(t_game *g, t_pos pos, int curr_img)
{
	if (g->map.rows[pos.y][pos.x] == collectible_token && curr_img == 0)
		put_tile_to_pos(g, g->tiles.collectible_1, pos);
	else if (g->map.rows[pos.y][pos.x] == collectible_token && curr_img == 1)
		put_tile_to_pos(g, g->tiles.collectible_2, pos);
	else if (g->map.rows[pos.y][pos.x] == collectible_token)
		put_tile_to_pos(g, g->tiles.collectible_3, pos);
}

int	render_next_frame(t_game *g)
{
	static int	frame;
	static int	curr_img;
	int			i;

	frame++;
	if (frame % 25000 != 0)
		return (0);
	i = 0;
	while ((g->map.collectibles_pos[i].y != -1))
	{
		animate_beer(g, g->map.collectibles_pos[i], curr_img);
		i++;
	}
	curr_img++;
	if (curr_img == 3)
		curr_img = 0;
	return (0);
}

void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		terminate_with_message(g, "Memory error\n");
	g->win = mlx_new_window(g->mlx, g->map.x * TILE_SIZE, g->map.y * TILE_SIZE,
			"so_long");
	if (!g->win)
		terminate_with_message(g, "Memory error\n");
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	parse(argv[1], &game);
	init_mlx(&game);
	init_xpm_tiles(&game);
	check_xmp_tiles(&game);
	render_initial_graphic(&game);
	mlx_key_hook(game.win, handle_keyboard_input, &game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
}
