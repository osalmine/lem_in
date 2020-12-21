/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 09:45:19 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 11:41:11 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

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
