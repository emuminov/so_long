/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:44:41 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/07 23:48:13 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		end_game(1, "Memory error\n", g);
	g->win = mlx_new_window(g->mlx, g->map.x * TILE_SIZE, g->map.y * TILE_SIZE,
			"so_long");
	if (!g->win)
		end_game(1, "Memory error\n", g);
}

void	put_tile_to_pos(t_game *g, void *tile, t_pos pos)
{
	mlx_put_image_to_window(g->mlx, g->win, tile, pos.x * TILE_SIZE, pos.y
		* TILE_SIZE);
}

static void	check_xmp_tiles(t_game *g)
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
	check_xmp_tiles(g);
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
