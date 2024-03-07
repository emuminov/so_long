/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:48:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/07 23:39:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static t_list	*read_map_to_list(int fd)
{
	t_list	*rows_list;
	t_list	*node;
	char	*curr_line;

	curr_line = get_next_line(fd);
	if (!curr_line)
		end_game(1, "Empty map\n", NULL);
	rows_list = ft_lstnew(curr_line);
	while (curr_line)
	{
		curr_line = get_next_line(fd);
		if (!curr_line)
			break ;
		node = ft_lstnew(curr_line);
		if (!node)
		{
			ft_lstclear(&rows_list, free);
			end_game(1, "Memory error while reading map\n", NULL);
		}
		ft_lstadd_back(&rows_list, node);
	}
	return (rows_list);
}

/* Initializes dimensions and checks if the map is rectangular or too big */
static void	check_dimensions(t_game *g)
{
	int	i;

	i = 0;
	g->map.x = ft_strlen(g->map.rows[0]);
	while (g->map.rows[i])
	{
		if ((int)ft_strlen(g->map.rows[i]) != g->map.x)
			end_game(1, "Map is not rectangular\n", g);
		i++;
	}
	g->map.y = i;
	if (g->map.y > 15 || g->map.x > 30)
		end_game(1, "Map is too big\n", g);
}

static void	remove_new_lines(char **rows)
{
	int	i;
	int	j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == '\n')
			{
				rows[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	get_collectibles_position(t_game *g)
{
	t_pos	*res;
	t_pos	pos;
	int		i;

	res = malloc(sizeof(t_pos) * (g->token_count.collectible_count + 1));
	if (!res)
		end_game(1, "Memory error\n", g);
	pos.y = 0;
	i = 0;
	while (g->map.rows[pos.y])
	{
		pos.x = 0;
		while (g->map.rows[pos.y][pos.x])
		{
			if (g->map.rows[pos.y][pos.x] == collectible_token)
				res[i++] = pos;
			pos.x++;
		}
		pos.y++;
	}
	res[i] = (t_pos){.x = -1, .y = -1};
	g->map.collectibles_pos = res;
}

void	parse(char *file, t_game *g)
{
	int		fd;
	t_list	*rows_list;

	check_filename_extension(file);
	fd = safe_open(file);
	rows_list = read_map_to_list(fd);
	safe_close(fd, rows_list);
	g->map.rows = list_to_matrix(rows_list);
	remove_new_lines(g->map.rows);
	check_dimensions(g);
	check_non_allowed_tokens(g);
	check_walls_presence(g);
	check_exit_and_collectibles_presence(g);
	check_exit_and_collectibles_availability(g);
	get_collectibles_position(g);
}
