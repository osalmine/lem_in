/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_and_link_table.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:46:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/30 16:34:14 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static void	assign_rooms_to_table(t_room **room_table, t_lem *lem)
{
	t_list	*rooms;
	int		i;

	rooms = lem->room_list;
	i = 0;
	while (rooms)
	{
		room_table[i] = ((t_room*)rooms->content);
		i++;
		rooms = rooms->next;
	}
}

void		create_room_table(t_lem *lem)
{
	t_room	**room_arr;

	if (!(room_arr = (t_room**)malloc(sizeof(t_room*) * lem->room_count)))
		ft_exit(RED"ERROR: malloc error"RESET);
	assign_rooms_to_table(room_arr, lem);
	lem->room_arr = room_arr;
}

static int	**alloc_room_links(t_lem *lem)
{
	int	**room_links;
	int i;
	int j;

	if (!(room_links = (int**)malloc(sizeof(int*) * lem->room_count)))
		ft_exit(RED"ERROR: malloc error"RESET);
	i = 0;
	while (i < lem->room_count)
	{
		j = 0;
		if (!(room_links[i] = (int*)malloc(sizeof(int) * lem->room_count)))
			ft_exit(RED"ERROR: malloc error"RESET);
		while (j < lem->room_count)
			room_links[i][j++] = -1;
		i++;
	}
	return (room_links);
}

static void	get_links(t_lem *lem, int **room_links)
{
	t_list	*rooms;
	t_list	*links;
	int		i;

	rooms = lem->room_list;
	i = 0;
	while (rooms)
	{
		links = ((t_room*)rooms->content)->links;
		while (links)
		{
			room_links[i][((t_link*)links->content)->room2->id] = \
				((t_link*)links->content)->room2->id;
			links = links->next;
		}
		i++;
		rooms = rooms->next;
	}
}

void		create_link_table(t_lem *lem)
{
	int	**room_links;

	room_links = alloc_room_links(lem);
	get_links(lem, room_links);
	lem->room_links_arr = room_links;
}
