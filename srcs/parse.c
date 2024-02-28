/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:48:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/28 10:51:21 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

typedef struct	s_map
{
	t_list	*rows;
	int		x;
	int		y;
}				t_map;

void	get_map_rows(int fd, t_map *map)
{
	t_list	*rows;
	t_list	*node;
	char	*curr_line;

	curr_line = get_next_line(fd);
	if (!curr_line)
	{
		ft_putstr_fd("Empty map\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	rows = ft_lstnew(curr_line);
	while (curr_line)
	{
		curr_line = get_next_line(fd);
		if (!curr_line)
			break ;
		node = ft_lstnew(curr_line);
		if (!node)
		{
			ft_lstclear(&rows, free);
			ft_putstr_fd("Memory error reading map\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&rows, node);
	}
	map->rows = rows;
}

/* Initializes dimensions and checks if the map is rectangular */
void	check_dimensions(t_map *map)
{
	t_list	*curr;

	curr = map->rows;
	map->x = ft_strlen(curr->content);
	map->y = ft_lstsize(curr);
	while (curr)
	{
		if ((int)ft_strlen(curr->content) != map->x)
		{
			ft_lstclear(&map->rows, free);
			ft_putstr_fd("Map is not rectangular\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		curr = curr->next;
	}
}

// TODO LIST:
// 1. Read and parse the map, check for map errors
//   - Map must have the .ber extension
//   - Map must have exit, collectible and starting position
//   - Map must not have duplicate exit and starting position
//   - Map must be surrounded by walls
//   - Map must be a rectangle
//   - Exit and collectibles must be reachable by player (no enemies,
//   walls etc are blocking them)
void	parse(char *file)
{
	int		fd;
	t_map	map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	get_map_rows(fd, &map);
	check_dimensions(&map);
}
