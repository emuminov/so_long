/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:48:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/28 17:08:53 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

typedef struct	s_map
{
	char	**rows;
	int		x;
	int		y;
}				t_map;

t_list	*read_map_to_list(int fd)
{
	t_list	*rows_list;
	t_list	*node;
	char	*curr_line;

	curr_line = get_next_line(fd);
	if (!curr_line)
	{
		ft_putstr_fd("Empty map\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
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
			ft_putstr_fd("Memory error reading map\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&rows_list, node);
	}
	return (rows_list);
}

/* Initializes dimensions and checks if the map is rectangular */
void	init_dimensions(t_map *map)
{
	int	i;

	i = 0;
	map->x = ft_strlen(map->rows[0]);
	while (map->rows[i])
	{
		if ((int)ft_strlen(map->rows[i]) != map->x)
		{
			ft_free_split(map->rows);
			ft_putstr_fd("Map is not rectangular\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	list_to_matrix(t_list *lst, t_map *map)
{
	char	**res;
	t_list	*curr;
	int		i;

	res = malloc(sizeof(char *) * (map->y + 1));
	if (!res)
	{
		ft_lstclear(&lst, free);
		ft_putstr_fd("Memory error reading map\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	curr = lst;
	i = 0;
	while (curr)
	{
		res[i] = curr->content;
		curr = curr->next;
		i++;
	}
	res[map->y] = NULL;
	map->rows = res;
}

void	remove_new_lines(char **rows)
{
	int		i;
	int		j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == '\n')
				rows[i][j] = '\0';
			j++;
		}
		i++;
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
	t_list	*rows_list;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	rows_list = read_map_to_list(fd);
	list_to_matrix(rows_list, &map);
	remove_new_lines(map.rows);
	init_dimensions(&map);
}
