/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/04 04:35:19 by emuminov         ###   ########.fr       */
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

void	init_xpm_tiles()
{
	
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_mlx	g;
	t_tiles	tiles;
	int tile_size = TILE_SIZE;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_bzero(&map, sizeof(map));
	parse(argv[1], &map);
	map.player_position.y = 3;
	map.player_position.x = 1;

	// init mlx and then clear every variable
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, map.x * TILE_SIZE, map.y * TILE_SIZE, "so_long");

	// init tiles
	// clear everything after
	tiles.wall = mlx_xpm_file_to_image(g.mlx, WALL_TILE_PATH, &tile_size, &tile_size);
	tiles.floor = mlx_xpm_file_to_image(g.mlx, FLOOR_TILE_PATH, &tile_size, &tile_size);
	tiles.player_left = mlx_xpm_file_to_image(g.mlx, PLAYER_LEFT_TILE_PATH, &tile_size, &tile_size);
	tiles.player_right = mlx_xpm_file_to_image(g.mlx, PLAYER_RIGHT_TILE_PATH, &tile_size, &tile_size);
	tiles.collectible_1 = mlx_xpm_file_to_image(g.mlx, COLLECTIBLE_1_TILE_PATH, &tile_size, &tile_size);
	tiles.collectible_2 = mlx_xpm_file_to_image(g.mlx, COLLECTIBLE_2_TILE_PATH, &tile_size, &tile_size);
	tiles.collectible_3 = mlx_xpm_file_to_image(g.mlx, COLLECTIBLE_3_TILE_PATH, &tile_size, &tile_size);
	tiles.enemy = mlx_xpm_file_to_image(g.mlx, ENEMY_TILE_PATH, &tile_size, &tile_size);
	tiles.exit = mlx_xpm_file_to_image(g.mlx, EXIT_TILE_PATH, &tile_size, &tile_size);

	// render tiles
	int i = 0;
	while (map.rows[i])
	{
		int j = 0;
		while (map.rows[i][j])
		{
			if (map.rows[i][j] == wall_token)
				mlx_put_image_to_window(g.mlx, g.win, tiles.wall, TILE_SIZE * j, TILE_SIZE * i);
			else if (map.rows[i][j] == floor_token)
				mlx_put_image_to_window(g.mlx, g.win, tiles.floor, TILE_SIZE * j, TILE_SIZE * i);
			else if (map.rows[i][j] == collectible_token)
				mlx_put_image_to_window(g.mlx, g.win, tiles.collectible_1, TILE_SIZE * j, TILE_SIZE * i);
			else if (map.rows[i][j] == enemy_token)
				mlx_put_image_to_window(g.mlx, g.win, tiles.enemy, TILE_SIZE * j, TILE_SIZE * i);
			else if (map.rows[i][j] == exit_token)
				mlx_put_image_to_window(g.mlx, g.win, tiles.exit, TILE_SIZE * j, TILE_SIZE * i);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(g.mlx, g.win, tiles.player_right, map.player_position.x * TILE_SIZE, map.player_position.y * TILE_SIZE);

	// init hooks and loop
	mlx_loop(g.mlx);
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
