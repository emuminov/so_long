/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:40:07 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/01 10:48:40 by emuminov         ###   ########.fr       */
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
