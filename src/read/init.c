/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 18:33:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/22 11:58:32 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	add_room_id(t_lem *lem)
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

t_lem		*lem_init(int ac, char **av)
{
	t_lem *lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_exit(RED"Malloc error"RESET);
	lem->ants = NULL;
	lem->link_list = NULL;
	lem->room_list = NULL;
	lem->paths_list = NULL;
	lem->paths_bef_ek = NULL;
	lem->moves_count = 0;
	if (!(lem->opts = (t_opts*)malloc(sizeof(t_opts))))
		ft_exit(RED"Malloc error"RESET);
	lem_flags(lem, ac, av);
	lem_read(lem);
	if (!(lem->start = find_room_by_type(START, lem)))
		ft_exit(RED"ERROR: start room not found"RESET);
	if (!(lem->end = find_room_by_type(END, lem)))
		ft_exit(RED"ERROR: end room not found"RESET);
	init_ants(lem);
	lem->room_count = room_count(lem);
	add_room_id(lem);
	create_room_table(lem);
	create_link_table(lem);
	return (lem);
}
