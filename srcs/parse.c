/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:48:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/06 14:20:32 by emuminov         ###   ########.fr       */
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
		terminate_with_message(NULL, "Empty map\n");
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
			terminate_with_message(NULL, "Memory error while reading map\n");
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
			terminate_with_message(g, "Map is not rectangular\n");
		i++;
	}
	g->map.y = i;
	if (g->map.y > 15 || g->map.x > 30)
		terminate_with_message(g, "Map is too big\n");
}

static char	**list_to_matrix(t_list *lst)
{
	char	**res;
	t_list	*curr;
	t_list	*next;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!res)
	{
		ft_lstclear(&lst, free);
		terminate_with_message(NULL, "Memory error\n");
	}
	curr = lst;
	i = 0;
	while (curr)
	{
		res[i] = curr->content;
		next = curr->next;
		free(curr);
		curr = next;
		i++;
	}
	res[i] = NULL;
	return (res);
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

void	get_collectibles_position(t_game *g)
{
	t_pos	*res;
	t_pos	pos;
	int		i;

	res = malloc(sizeof(t_pos) * (g->token_count.collectible_count + 1));
	if (!res)
		terminate_with_message(g, "Memory error\n");
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
