/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:43:40 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/08 11:55:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	render_player_position(t_pos new_pos, t_game *g)
{
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
}

static void	update_move_count(t_game *g)
{
	char	*player_moves_count_str;

	g->player_moves_count++;
	player_moves_count_str = ft_itoa(g->player_moves_count);
	if (!player_moves_count_str)
		end_game(1, "Memory error\n", g);
	put_tile_to_pos(g, g->tiles.wall, (t_pos){.x = 0, .y = 0});
	put_tile_to_pos(g, g->tiles.wall, (t_pos){.x = 1, .y = 0});
	mlx_string_put(g->mlx, g->win, TILE_SIZE / 2, TILE_SIZE / 2, 0xADD8E6,
		player_moves_count_str);
	free(player_moves_count_str);
}

static void	move_player(t_pos new_pos, t_game *g)
{
	if (g->map.rows[new_pos.y][new_pos.x] == wall_token)
		return ;
	else if (g->map.rows[new_pos.y][new_pos.x] == collectible_token)
	{
		g->map.rows[new_pos.y][new_pos.x] = floor_token;
		g->collected_count++;
	}
	else if (g->map.rows[new_pos.y][new_pos.x] == enemy_token)
		end_game(0, "You lost! 😔\n", g);
	else if (g->map.rows[new_pos.y][new_pos.x] == exit_token
		&& g->collected_count == g->token_count.collectible_count)
		end_game(0, "You won! 🎉\n", g);
	render_player_position(new_pos, g);
	update_move_count(g);
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
