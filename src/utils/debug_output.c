/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:56:11 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 12:04:33 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	link_list_out(t_lem *lem)
{
	t_list	*tmp_rooms;
	t_link	*link;

	ft_printf(RED"LEM LINK LIST:\n"RESET);
	tmp_rooms = lem->link_list;
	while (tmp_rooms)
	{
		link = (t_link*)tmp_rooms->content;
		ft_printf("Link room1: %s, ptr: %p, room2: %s, ptr: %p\n", \
			link->room1->name, link->room1, link->room2->name, link->room2);
		tmp_rooms = tmp_rooms->next;
	}
	write(1, "\n\n\n", 3);
}

static void	debug_while(t_list *tmp_rooms)
{
	t_room	*new_room;
	t_link	*link;
	t_list	*tmp;

	new_room = (t_room*)tmp_rooms->content;
	ft_printf("Size of room struct: %d, room name addr: %p, size %d\n", \
		sizeof(t_room), new_room->name, sizeof(new_room->name));
	ft_printf("Room name: %s, ptr: %p, id: %d, room type: %d, x: %d, y: \
%d, visited: %d, has_ant: %d\n", new_room->name, new_room, new_room->id, \
new_room->type, new_room->x, new_room->y, new_room->visited, new_room->has_ant);
	tmp = new_room->links;
	while (tmp)
	{
		link = (t_link*)tmp->content;
		ft_printf(BLUE"Link room1: %s, pt: %p, room2: %s, pt: %p\n"RESET, \
			link->room1->name, link->room1, link->room2->name, link->room2);
		tmp = tmp->next;
	}
}

void		debug_out(t_lem *lem)
{
	t_lem	*lem_tmp;
	t_list	*tmp_rooms;

	ft_printf("number of ants: %d\n", lem->ant_nb);
	lem_tmp = lem;
	tmp_rooms = (t_list*)lem_tmp->room_list;
	while (tmp_rooms)
	{
		debug_while(tmp_rooms);
		tmp_rooms = tmp_rooms->next;
	}
	link_list_out(lem);
}
