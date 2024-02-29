/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:51:11 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/29 14:20:49 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <X11/keysym.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

enum e_tokens
{
	empty_tile = '0',
	wall_tile = '1',
	player_tile = 'P',
	collectible_tile = 'C',
	exit_tile = 'E',
	enemy_tile = 'V',
	occupied_tile = '-'
};

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos; 

typedef struct	s_map
{
	t_pos	player_position;
	char	**rows;
	int		x;
	int		y;
	int		player_count;
	int		collectible_count;
	int		exit_count;
}				t_map;

void	parse(char *file, t_map *map);
void	id(void *ptr);

#endif 
