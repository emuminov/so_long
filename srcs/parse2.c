/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:40:07 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/07 23:37:10 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	safe_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("fd error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	safe_close(int fd, t_list *lst)
{
	if (close(fd) < 0)
	{
		ft_lstclear(&lst, free);
		ft_putstr_fd("fd error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (1);
}

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

char	**list_to_matrix(t_list *lst)
{
	char	**res;
	t_list	*curr;
	t_list	*next;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!res)
	{
		ft_lstclear(&lst, free);
		end_game(1, "Memory error\n", NULL);
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

void	check_filename_extension(char *file)
{
	int		len;
	char	*ext;

	len = ft_strlen(file);
	if (len < 4)
		end_game(1, "Bad filename\n", NULL);
	ext = ft_strnstr(&file[len - 4], ".ber", 4);
	if (!ext)
		end_game(1, "Bad extension\n", NULL);
}
