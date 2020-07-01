/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/30 20:26:39 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int	main(int argc, char **argv)
{
	t_lem	*lem;

	char red[] = "\x1b[31m";
	ft_printf(RED"RED\n"RESET);
	lem = lem_init(argc, argv);
	if (lem->opts->debug)
	{
		ft_printf("number of ants: %d\n", lem->ant_nb);
		t_lem *lem_tmp;
		t_path *path;
		lem_tmp = lem;
		while (lem_tmp->room_list->next)
		{
			t_room *new_room;
			new_room = (t_room*)lem_tmp->room_list->content;
			ft_printf("Room name: %s, room type: %d, x: %d, y: %d, visited: %d, has_ant: %d\n", new_room->name, new_room->type, new_room->x, new_room->y, new_room->visited, new_room->has_ant);
			t_list *tmp;

			tmp = new_room->paths;
			while (tmp && tmp->next)
			{
				path = (t_path*)tmp->content;
				ft_printf("Path room1: %s, room2: %s\n", path->room1, path->room2);
				tmp = tmp->next;
			}
			lem_tmp->room_list = lem_tmp->room_list->next;
		}
		ft_printf(RED"LEM PATH LIST:\n"RESET);
		lem_tmp = lem;
		while (lem_tmp->path_list->next)
		{
			path = (t_path*)lem_tmp->path_list->content;
			ft_printf("Path room1: %s, room2: %s\n", path->room1, path->room2);
			lem_tmp->path_list = lem_tmp->path_list->next;
		}
	}
	guide_ants(lem);
	return (0);
}
