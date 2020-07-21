/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 18:33:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/08 20:58:24 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void  add_room_id(t_lem* lem)
{
	int		id;
	t_list	*tmp;
	t_room	*room;

	id = 0;
	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->id = id;
		id++;
		tmp = tmp->next;
	}
}

t_lem	*lem_init(int ac, char **av)
{
	t_lem *lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_exit("Malloc error\n");
	lem->ants = NULL;
	lem->path_list = NULL;
	lem->room_list = NULL;
	if (!(lem->opts = (t_opts*)malloc(sizeof(t_opts))))
		ft_exit("Malloc error\n");
	lem_flags(lem, ac, av);
	lem_read(lem);
	add_room_id(lem);
	init_ants(lem);
	return (lem);
}
