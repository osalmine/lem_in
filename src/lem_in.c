/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/06 09:39:05 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int	main(int argc, char **argv)
{
	t_lem	*lem;

	lem = lem_init(argc, argv);
	if (lem->opts->debug)
	{
		ft_printf("number of ants: %d\n", lem->ant_nb);
		t_lem *lem_tmp;
		t_link *link;
		lem_tmp = lem;
		t_list *tmp_rooms;
		tmp_rooms = (t_list*)lem_tmp->room_list;
		while (tmp_rooms)
		{
			t_room *new_room;
			new_room = (t_room*)tmp_rooms->content;
			ft_printf("Room name: %s, id: %d, room type: %d, x: %d, y: %d, visited: %d, has_ant: %d\n", new_room->name, new_room->id, new_room->type, new_room->x, new_room->y, new_room->visited, new_room->has_ant);
			t_list *tmp;

			tmp = new_room->links;
			while (tmp)
			{
				link = (t_link*)tmp->content;
				ft_printf(BLUE"Link room1: %s, room2: %s\n"RESET, link->room1, link->room2);
				tmp = tmp->next;
			}
			tmp_rooms = tmp_rooms->next;
		}
		ft_printf(RED"LEM LINK LIST:\n"RESET);
		tmp_rooms = lem->link_list;
		while (tmp_rooms)
		{
			link = (t_link*)tmp_rooms->content;
			ft_printf("Link room1: %s, room2: %s\n", link->room1, link->room2);
			tmp_rooms = tmp_rooms->next;
		}
		write(1, "\n\n\n", 3);
	}
	guide_ants(lem);
	if (lem->opts->lines)
		ft_printf(GREEN BOLD"lines: %d\n"RESET, lem->moves_count);
	free_lem(lem);
	// while (1) ;
	return (0);
}
