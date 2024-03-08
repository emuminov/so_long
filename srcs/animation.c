/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:46:57 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/08 11:07:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	animate_beer(t_game *g, t_pos pos, int curr_img)
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
	if (frame % 20000 != 0)
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
