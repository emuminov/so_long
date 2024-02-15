/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/15 13:42:27 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <X11/keysym.h>
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
	printf("Hello! %d %d\n", x, y);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 6, 1L<<6, mousemovehook, &vars);
	// mlx_key_hook(vars.win, keyhook, &vars);
	// mlx_mouse_hook(vars.win, mousehook, &vars);
	mlx_loop(vars.mlx);
}
