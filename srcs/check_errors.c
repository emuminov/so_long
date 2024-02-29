/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:52:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/29 10:35:44 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// TODO LIST:
// 1. Read and parse the map, check for map errors
//   - [x] Map must have the .ber extension
//   - [x] Map must be surrounded by walls
//   - [x] Map must have exit, collectible and starting position
//   - [x] Map must not have duplicate exit and starting position
//   - [x] Map must be a rectangle (init_dimensions)
//   - Exit and collectibles must be reachable by player (no enemies,
//   walls etc are blocking them)

void	check_extension(char *file)
{
	int		len;
	char	*ext;

	len = ft_strlen(file);
	if (len < 4)
	{
		ft_putstr_fd("Bad filename\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ext = ft_strnstr(&file[len - 4], ".ber", 4);
	if (!ext)
	{
		ft_putstr_fd("Bad extension\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	check_tokens(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->exit_count = 0;
	map->player_count = 0;
	map->collectible_count = 0;
	while (map->rows[i])
	{
		j = 0;
		while (map->rows[i][j])
		{
			if (map->rows[i][j] == player_tile)
				map->player_count++;	
			if (map->rows[i][j] == exit_tile)
				map->exit_count++;	
			if (map->rows[i][j] == collectible_tile)
				map->collectible_count++;
			if (map->player_count > 1 || map->exit_count > 1 ||
				map->player_count == 0 || map->exit_count == 0 ||
				map->collectible_count == 0)
			{
				ft_putstr_fd("Bad map", STDERR_FILENO);
				ft_free_split(map->rows);
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->x)
	{
		if (map->rows[0][i] != wall_tile ||
			map->rows[map->y][i] != wall_tile)
		{
			ft_putstr_fd("Bad walls\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < map->y)
	{
		if (map->rows[i][0] != wall_tile ||
			map->rows[i][map->x] != wall_tile)
		{
			ft_putstr_fd("Bad walls\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_errors(t_map *map)
{
	// check_extension(map);
	// check_walls(map);
	// check_tokens_number(map);
	// check_tokens_availability(map);
}
