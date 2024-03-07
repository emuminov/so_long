/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:52:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/07 23:37:12 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_exit_and_collectibles_presence(t_game *g)
{
	t_pos	pos;

	pos.y = 0;
	while (g->map.rows[pos.y])
	{
		pos.x = 0;
		while (g->map.rows[pos.y][pos.x])
		{
			if (g->map.rows[pos.y][pos.x] == player_token)
			{
				g->token_count.player_count++;
				g->map.player_pos = pos;
			}
			else if (g->map.rows[pos.y][pos.x] == exit_token)
				g->token_count.exit_count++;
			else if (g->map.rows[pos.y][pos.x] == collectible_token)
				g->token_count.collectible_count++;
			pos.x++;
		}
		pos.y++;
	}
	if (g->token_count.player_count > 1 || g->token_count.exit_count > 1
		|| g->token_count.player_count == 0 || g->token_count.exit_count == 0
		|| g->token_count.collectible_count == 0)
		end_game(1, "Bad map\n", g);
}

void	check_walls_presence(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->map.x)
	{
		if (g->map.rows[0][i] != wall_token || g->map.rows[g->map.y
			- 1][i] != wall_token)
			end_game(1, "Bad walls\n", g);
		i++;
	}
	i = 0;
	while (i < g->map.y)
	{
		if (g->map.rows[i][0] != wall_token || g->map.rows[i][g->map.x
			- 1] != wall_token)
			end_game(1, "Bad walls\n", g);
		i++;
	}
}

void	check_non_allowed_tokens(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map.rows[i])
	{
		j = 0;
		while (g->map.rows[i][j])
		{
			if (g->map.rows[i][j] != floor_token
				&& g->map.rows[i][j] != wall_token
				&& g->map.rows[i][j] != collectible_token
				&& g->map.rows[i][j] != exit_token
				&& g->map.rows[i][j] != player_token
				&& g->map.rows[i][j] != enemy_token)
				end_game(1, "Bad token\n", g);
			j++;
		}
		i++;
	}
}

static void	propagate_tokens(t_pos pos, char **rows)
{
	if (rows[pos.y][pos.x] == wall_token || rows[pos.y][pos.x] == enemy_token
		|| rows[pos.y][pos.x] == occupied_token || pos.y < 0 || pos.x < 0)
		return ;
	if (rows[pos.y][pos.x] != player_token)
		rows[pos.y][pos.x] = occupied_token;
	propagate_tokens((t_pos){.x = pos.x - 1, .y = pos.y}, rows);
	propagate_tokens((t_pos){.x = pos.x + 1, .y = pos.y}, rows);
	propagate_tokens((t_pos){.x = pos.x, .y = pos.y - 1}, rows);
	propagate_tokens((t_pos){.x = pos.x, .y = pos.y + 1}, rows);
}

void	check_exit_and_collectibles_availability(t_game *g)
{
	char	**cloned_map;
	int		i;

	cloned_map = clone_matrix(g->map.y, g->map.rows);
	if (!cloned_map)
		end_game(1, "Memory error\n", g);
	propagate_tokens(g->map.player_pos, cloned_map);
	i = 0;
	while (cloned_map[i])
	{
		if (ft_strchr(cloned_map[i], exit_token) || ft_strchr(cloned_map[i],
				collectible_token))
		{
			ft_free_split(cloned_map);
			end_game(1, "Inaccessible exit or collectible\n", g);
		}
		i++;
	}
	ft_free_split(cloned_map);
}
