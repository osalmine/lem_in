/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 09:45:19 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/09 23:05:05 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void		free_strsplit(char ***str)
{
	char **curr;

	if (str && *str)
	{
		curr = (*str);
		while (*curr)
			free(*(curr++));
		free(*str);
		*str = NULL;
		str = NULL;
	}
}

void		free_link(void *link, size_t size)
{
	size = 0;
	ft_memdel(&link);
}

void		free_room(void *room, size_t size)
{
	size = 0;
	ft_strdel(&((t_room*)room)->name);
	ft_memdel(&room);
}

void	free_a_path(t_path **path, size_t size)
{
	size = 0;
	free(path);
	// ft_printf("path arr address: %p\n", (*path)->path_arr);
	// ft_printf("path colour: %s aa\n", (*path)->colour);
	if ((*path)->colour)
		ft_strdel(&(*path)->colour);
	// ft_printf("path clolour address: %p\n", (*path)->colour);
	ft_memdel((void**)&(*path));
	// ft_printf("return free_a_path\n");
}

static void	free_path(void *path, size_t size)
{
	size = 0;
	if (((t_path*)path)->colour)
		ft_strdel(&((t_path*)path)->colour);
	ft_memdel(&path);
}

static void	free_ant(void *ant, size_t size)
{
	size = 0;
	ft_memdel(&ant);
}

void		free_lem(t_lem *lem)
{
	ft_memdel((void**)&lem->opts);
	ft_lstdel(&lem->link_list, free_link);
	ft_lstdel(&lem->room_list, free_room);
	ft_lstdel(&lem->paths_list, free_path);
	ft_lstdel(&lem->ants, free_ant);
	ft_memdel((void**)&lem);
}