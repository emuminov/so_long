/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/27 16:31:56 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int keyhook(int keycode, t_vars *vars)
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

int mousemovehook(int x, int y, t_vars *vars)
{
	(void)vars;
	printf("Hello! %d %d\n", x, y);
	return (0);
}

// TODO LIST:
// 1. Read and parse the map, check for map errors
// https://github.com/Axiaaa
int	main(void)
{
	void	*image;
	t_vars	vars;
	int 	width;
	int 	height;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (EXIT_FAILURE);
	vars.win = mlx_new_window(vars.mlx, 600, 400, "Hello world!");

	width = 900;
	height = 900;
	image = mlx_xpm_file_to_image(vars.mlx, "./us.xpm", &width, &height);
	mlx_put_image_to_window(vars.mlx, vars.win, image, 0, 0);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
