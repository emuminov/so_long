/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:56:51 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/08 11:09:31 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_mlx(t_game *g)
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
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	free(g->mlx);
}

void	end_game(int is_error, char *msg, t_game *g)
{
	if (g)
	{
		if (g->mlx)
			free_mlx(g);
		ft_free_split(g->map.rows);
		free(g->map.collectibles_pos);
	}
	if (msg && !is_error)
		ft_putstr_fd(msg, STDOUT_FILENO);
	else if (msg && is_error)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (is_error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
		return (EXIT_FAILURE);
	parse(argv[1], &game);
	init_mlx(&game);
	init_xpm_tiles(&game);
	render_initial_graphic(&game);
	mlx_key_hook(game.win, handle_keyboard_input, &game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
}
