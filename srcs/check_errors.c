/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:52:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/01 10:37:57 by emuminov         ###   ########.fr       */
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
//   - [x] Exit and collectibles must be reachable by player (no enemies,
//   walls etc are blocking them)

void	check_filename_extension(char *file)
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

void	check_exit_and_collectibles_presence(t_token_count *tc, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->rows[i])
	{
		j = 0;
		while (map->rows[i][j])
		{
			if (map->rows[i][j] == player_tile)
			{
				tc->player_count++;	
				map->player_position.y = i;
				map->player_position.x = j;
			}
			if (map->rows[i][j] == exit_tile)
				tc->exit_count++;	
			if (map->rows[i][j] == collectible_tile)
				tc->collectible_count++;
			if (tc->player_count > 1 || tc->exit_count > 1 ||
				tc->player_count == 0 || tc->exit_count == 0 ||
				tc->collectible_count == 0)
			{
				ft_putstr_fd("Bad map", STDERR_FILENO);
				ft_free_split(map->rows);
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	check_walls_presence(t_map *map)
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

// TODO: handle potential errors in this function
char	**clone_matrix(int l, char **matrix)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (l + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		res[i] = ft_strdup(matrix[i]);
		if (!res[i])
		{
			ft_free_split(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	propagate_tokens(t_pos pos, char **rows)
{
	if (rows[pos.y][pos.x] == wall_tile ||
		rows[pos.y][pos.x] == enemy_tile ||
		rows[pos.y][pos.x] == occupied_tile ||
		pos.y < 0 || pos.x < 0)
		return ;
	if (rows[pos.y][pos.x] != player_tile)
		rows[pos.y][pos.x] = occupied_tile;
	propagate_tokens((t_pos){.x=pos.x - 1, .y=pos.y}, rows);
	propagate_tokens((t_pos){.x=pos.x + 1, .y=pos.y}, rows);
	propagate_tokens((t_pos){.x=pos.x, .y=pos.y - 1}, rows);
	propagate_tokens((t_pos){.x=pos.x, .y=pos.y + 1}, rows);
}

void	check_exit_and_collectibles_availability(t_map *map)
{
	char	**cloned_map;
	int		i;

	cloned_map = clone_matrix(map->y, map->rows);
	if (!cloned_map)
	{
		ft_free_split(map->rows);
		ft_putstr_fd("Memory error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	propagate_tokens(map->player_position, cloned_map);
	i = 0;
	while (cloned_map[i])
	{
		if (ft_strchr(cloned_map[i], exit_tile) ||
			ft_strchr(cloned_map[i], collectible_tile))
		{
			ft_free_split(map->rows);
			ft_free_split(cloned_map);
			ft_putstr_fd("Inaccessible exit or collectible\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
