/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:48:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/05 14:56:06 by emuminov         ###   ########.fr       */
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
			ft_putstr_fd("Memory error while reading map\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&rows_list, node);
	}
	return (rows_list);
}

/* Initializes dimensions and checks if the map is rectangular or too big */
static void	check_dimensions(t_game *game)
{
	int	i;

	i = 0;
	game->map.x = ft_strlen(game->map.rows[0]);
	while (game->map.rows[i])
	{
		if ((int)ft_strlen(game->map.rows[i]) != game->map.x)
			terminate_with_message(game, "Map is not rectangular\n");
		i++;
	}
	game->map.y = i;
	if (game->map.y > 15 || game->map.x > 30)
		terminate_with_message(game, "Map is too big\n");
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
	int		i;
	int		j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == '\n')
			{
				rows[i][j] = '\0';
				break;
			}
			j++;
		}
		i++;
	}
}

void	parse(char *file, t_game *game)
{
	int				fd;
	t_list			*rows_list;

	check_filename_extension(file);
	fd = safe_open(file);
	rows_list = read_map_to_list(fd);
	safe_close(fd, rows_list);
	game->map.rows = list_to_matrix(rows_list);
	remove_new_lines(game->map.rows);
	check_dimensions(game);
	check_non_allowed_tokens(game);
	check_walls_presence(game);
	check_exit_and_collectibles_presence(game);
	check_exit_and_collectibles_availability(game);
}
