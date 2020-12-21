/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:41:33 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/19 18:26:45 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static void		check_room_dups(t_lem *lem, char **room_arr)
{
	t_list *rooms;

	rooms = lem->room_list;
	while (rooms)
	{
		if (((t_room*)rooms->content)->x == ft_atoi(room_arr[1]) && \
			((t_room*)rooms->content)->y == ft_atoi(room_arr[2]))
			ft_exit(RED"ERROR: duplicated coordinates"RESET);
		rooms = rooms->next;
	}
	if (lem->room_list && find_room(room_arr[0], lem))
		ft_exit(RED"ERROR: duplicated room name"RESET);
}

static t_room	init_room(t_lem *lem, char **room_arr, int room_type)
{
	t_room room;

	room.name = ft_strdup(room_arr[0]);
	if (!ft_isdigit(room_arr[1][0]) || !ft_isdigit(room_arr[2][0]))
		ft_exit(RED"ERROR: room coordinate is not a number"RESET);
	room.x = ft_atoi(room_arr[1]);
	room.y = ft_atoi(room_arr[2]);
	room.visited = FALSE;
	if (room_type == START)
		room.has_ant = lem->ant_nb;
	else
		room.has_ant = FALSE;
	room.type = room_type;
	room.links = NULL;
	room.weight = INF - 1;
	return (room);
}

void			read_room(t_lem *lem, char *line, \
					int *room_type, int format_check)
{
	char	**room_arr;
	t_room	room;

	if (format_check == 2)
		ft_exit(RED"ERROR: input format error"RESET);
	room_arr = ft_strsplit(line, ' ');
	check_room_dups(lem, room_arr);
	if (arr_size(room_arr) != 3 || room_arr[0][0] == 'L')
		ft_exit(RED"ERROR: room error"RESET);
	room = init_room(lem, room_arr, *room_type);
	*room_type = NORMAL;
	free_strsplit(&room_arr);
	ft_lstaddlast(&lem->room_list, ft_lstnew(&room, sizeof(t_room)));
}
