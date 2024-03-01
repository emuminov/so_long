/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/01 12:07:16 by emuminov         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_bzero(&map, sizeof(map));
	parse(argv[1], &map);
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
