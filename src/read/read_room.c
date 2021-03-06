/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:41:33 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 15:01:28 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static void		check_room_dups(t_lem *lem, char **room_arr)
{
	t_room *room;

	if ((room = find_hashed_room(lem, room_arr[0])))
		ft_exit(RED"ERROR: duplicated room name"RESET);
}

static t_room	init_room(t_lem *lem, char **room_arr, int room_type)
{
	t_room room;

	room.name = ft_strdup(room_arr[0]);
	if (!ft_isdigit(room_arr[1][0]) || !ft_isdigit(room_arr[2][0]))
		ft_exit(RED"ERROR: room coordinate is not a number"RESET);
	room.x = get_number(room_arr[1]);
	room.y = get_number(room_arr[2]);
	room.visited = FALSE;
	room.visited_ek = FALSE;
	if (room_type == START)
		room.has_ant = lem->ant_nb;
	else
		room.has_ant = FALSE;
	room.type = room_type;
	room.links = NULL;
	room.in_path = FALSE;
	return (room);
}

void			read_room(t_lem *lem, char *line, \
					int *room_type, int format_check)
{
	char	**room_arr;
	t_room	room;
	t_list	*list;

	if (format_check == 2)
		ft_exit(RED"ERROR: input format error"RESET);
	room_arr = ft_strsplit(line, ' ');
	check_room_dups(lem, room_arr);
	if (arr_size(room_arr) != 3 || room_arr[0][0] == 'L')
		ft_exit(RED"ERROR: room error"RESET);
	room = init_room(lem, room_arr, *room_type);
	*room_type = NORMAL;
	free_strsplit(&room_arr);
	ft_lstadd(&lem->room_list, ft_lstnew(&room, sizeof(t_room)));
	if (!(list = (t_list *)malloc(sizeof(t_list))))
		ft_exit(RED"ERROR: malloc error"RESET);
	list->content = lem->room_list->content;
	list->content_size = lem->room_list->content_size;
	list->next = NULL;
	ft_lstaddlast(&lem->room_hash_table \
		[hash(room.name, lem->room_count * 1.5)], list);
}
