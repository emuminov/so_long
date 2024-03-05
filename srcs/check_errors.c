/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:52:31 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/05 15:07:19 by emuminov         ###   ########.fr       */
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
//   - [x] Map should not be too big
//   - [x] There should be no non-allowed symbols

void	terminate_with_message(t_game *game, char *msg)
{
	if (!game)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (game->map.rows)
		ft_free_split(game->map.rows);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	check_filename_extension(char *file)
{
	int		len;
	char	*ext;

	len = ft_strlen(file);
	if (len < 4)
		terminate_with_message(NULL, "Bad filename\n");
	ext = ft_strnstr(&file[len - 4], ".ber", 4);
	if (!ext)
		terminate_with_message(NULL, "Bad extension\n");
}

void	check_exit_and_collectibles_presence(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.rows[i])
	{
		j = 0;
		while (game->map.rows[i][j])
		{
			if (game->map.rows[i][j] == player_token)
			{
				game->token_count.player_count++;	
				game->map.player_pos.y = i;
				game->map.player_pos.x = j;
			}
			else if (game->map.rows[i][j] == exit_token)
				game->token_count.exit_count++;	
			else if (game->map.rows[i][j] == collectible_token)
				game->token_count.collectible_count++;
			j++;
		}
		i++;
	}
	if (game->token_count.player_count > 1 || game->token_count.exit_count > 1 ||
			game->token_count.player_count == 0 || game->token_count.exit_count == 0 ||
			game->token_count.collectible_count == 0)
		terminate_with_message(game, "Bad map\n");
}

void	check_walls_presence(t_game *game) {
	int	i;

	i = 0;
	while (i < game->map.x)
	{
		if (game->map.rows[0][i] != wall_token ||
			game->map.rows[game->map.y - 1][i] != wall_token)
			terminate_with_message(game, "Bad walls\n");
		i++;
	}
	i = 0;
	while (i < game->map.y)
	{
		if (game->map.rows[i][0] != wall_token ||
			game->map.rows[i][game->map.x - 1] != wall_token)
			terminate_with_message(game, "Bad walls\n");
		i++;
	}
}

void	check_non_allowed_tokens(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.rows[i])
	{
		j = 0;
		while (game->map.rows[i][j])
		{
			if (game->map.rows[i][j] != floor_token &&
				game->map.rows[i][j] != wall_token &&
				game->map.rows[i][j] != collectible_token &&
				game->map.rows[i][j] != exit_token &&
				game->map.rows[i][j] != player_token &&
				game->map.rows[i][j] != enemy_token)
			{
				ft_free_split(game->map.rows);
				ft_putstr_fd("Bad token\n", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

static void	propagate_tokens(t_pos pos, char **rows)
{
	if (rows[pos.y][pos.x] == wall_token ||
		rows[pos.y][pos.x] == enemy_token ||
		rows[pos.y][pos.x] == occupied_token ||
		pos.y < 0 || pos.x < 0)
		return ;
	if (rows[pos.y][pos.x] != player_token)
		rows[pos.y][pos.x] = occupied_token;
	propagate_tokens((t_pos){.x=pos.x - 1, .y=pos.y}, rows);
	propagate_tokens((t_pos){.x=pos.x + 1, .y=pos.y}, rows);
	propagate_tokens((t_pos){.x=pos.x, .y=pos.y - 1}, rows);
	propagate_tokens((t_pos){.x=pos.x, .y=pos.y + 1}, rows);
}

void	check_exit_and_collectibles_availability(t_game *game)
{
	char	**cloned_map;
	int		i;

	cloned_map = clone_matrix(game->map.y, game->map.rows);
	if (!cloned_map)
	{
		ft_free_split(game->map.rows);
		ft_putstr_fd("Memory error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	propagate_tokens(game->map.player_pos, cloned_map);
	i = 0;
	while (cloned_map[i])
	{
		if (ft_strchr(cloned_map[i], exit_token) ||
			ft_strchr(cloned_map[i], collectible_token))
		{
			ft_free_split(game->map.rows);
			ft_free_split(cloned_map);
			ft_putstr_fd("Inaccessible exit or collectible\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_free_split(cloned_map);
}
