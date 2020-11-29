/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:46:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/11/28 21:55:03 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static t_room	***allocate_table(int room_nb)
{
	t_room	***room_table;
	int		i;
	int		j;

	i = 0;
	if (!(room_table = (t_room***)malloc(sizeof(t_room**) * room_nb)))
		ft_exit(RED"ERROR: malloc error"RESET);
	while (i < room_nb)
	{
		j = 0;
		if (!(room_table[i] = (t_room**)malloc(sizeof(t_room*) * room_nb)))
			ft_exit(RED"ERROR: malloc error"RESET);
		while (j < room_nb)
			room_table[i][j++] = NULL;
		i++;
	}
	return (room_table);
}

static void		assign_rooms_to_table(t_room ***room_table, t_lem *lem)
{
	t_list	*rooms;
	t_list	*links;
	int		i;
	int		j;

	rooms = lem->room_list;
	i = 0;
	j = 0;
	while (rooms)
	{
		room_table[i][j++] = ((t_room*)rooms->content);
		links = ((t_room*)rooms->content)->links;
		while (links)
		{
			room_table[i][((t_link*)links->content)->room2->id] = ((t_link*)links->content)->room2;
			links = links->next;
		}
		i++;
		rooms = rooms->next;
	}
}

void			create_room_table(t_lem *lem)
{
	t_room	***room_table;

	room_table = allocate_table(lem->room_nb);
	assign_rooms_to_table(room_table, lem);
	lem->room_table = room_table;
	for (int i = 0; i < lem->room_nb; i++)
		for (int j = 0; j < lem->room_nb; j++)
			ft_printf("room_table[%d][%d]->name: %s, ->id: %d, ptr: %p\n", i, j, room_table[i][j] ? room_table[i][j]->name : NULL, room_table[i][j] ? room_table[i][j]->id : -1, room_table[i][j]);
}