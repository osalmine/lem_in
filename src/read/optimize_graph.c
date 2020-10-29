/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:36:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/26 13:25:14 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static void	remove_links_to_room(t_list **links, t_room *removed_room)
{
	t_list *links_list;
	t_list *prev;

	links_list = *links;
	prev = NULL;
	// ft_printf("remove links to room\n");
	while (links_list)
	{
		// ft_printf("AA\n");
		if (ft_strequ(((t_link*)links_list->content)->room2, removed_room->name))
		{
			// ft_printf("matching link: room2: %s, removed_room: %s\n", ((t_link*)links_list->content)->room2, removed_room->name);
			// ft_printf("BEF prev ptr: %p, prev next: %p, link_list: %p, link_list next: %p\n", prev, prev ? prev->next : NULL, links_list, links_list->next);
			if (!prev)
				*links = links_list->next;
			else
				prev->next = links_list->next;
			// ft_printf("AFT prev ptr: %p, prev next: %p, link_list: %p, link_list next: %p\n", prev, prev ? prev->next : NULL, links_list, links_list->next);
			// free_link(((t_link*)links_list->content), sizeof(t_link));
			return ;
		}
		prev = links_list;
		links_list = links_list->next;
	}
}

static void	link_list_remove(t_list **list, t_room *room1, t_room *room2)
{
	t_link *link;
	t_list *link_list;
	t_list *prev;

	link_list = *list;
	prev = NULL;
	// ft_printf("link list remove\n");
	while (link_list)
	{
		// ft_printf("OK\n");
		if ((ft_strequ(((t_link*)link_list->content)->room1, room1->name) && \
			ft_strequ(((t_link*)link_list->content)->room2, room2->name)) || \
			(ft_strequ(((t_link*)link_list->content)->room2, room1->name) && \
			ft_strequ(((t_link*)link_list->content)->room1, room2->name)))
		{
			// ft_printf("matching link: room1: %s, room2: %s\n", ((t_link*)link_list->content)->room1, ((t_link*)link_list->content)->room2);
			// ft_printf("BEF prev ptr: %p, prev next: %p, link_list: %p, link_list next: %p\n", prev, prev ? prev->next : NULL, link_list, link_list->next);
			if (!prev)
				*list = link_list->next;
			else
				prev->next = link_list->next;
			// ft_printf("AFT prev ptr: %p, prev next: %p, link_list: %p, link_list next: %p\n", prev, prev ? prev->next : NULL, link_list, link_list->next);
			link = ((t_link*)link_list->content);
			remove_links_to_room(&(room2->links), room1);
			free_link((void*)link, sizeof(t_link));
			link = NULL;
		}
		if (!prev || prev->next != link_list->next)
			prev = link_list;
		link_list = link_list->next;
	}
	// ft_printf("link list remove done\n");
}

static void	remove_room(t_list **rooms, t_room *room)
{
	t_list *rooms_list;
	t_list *prev;

	rooms_list = *rooms;
	prev = NULL;

	while (rooms_list && room)
	{
		if (ft_strequ(((t_room*)rooms_list->content)->name, room->name))
		{
			if (!prev)
				*rooms = rooms_list->next;
			else
				prev->next = rooms_list->next;
			free_room(((t_room*)rooms_list->content), sizeof(t_room));
			return ;
		}
		prev = rooms_list;
		rooms_list = rooms_list->next;
	}
}

void    	remove_dead_ends(t_lem *lem)
{
    t_list	*rooms;
	t_list	*room_links;
	t_room	*room2;
    int		link_count;
	int		new_loop;

	new_loop = 1;
	while (new_loop)
	{
		new_loop = 0;
		rooms = lem->room_list;
		// ft_printf(GREEN"rooms ptr: %p\n"RESET, rooms);
		while (rooms)
		{
			link_count = 0;
			room_links = ((t_room*)rooms->content)->links;
			if (((t_room*)rooms->content)->type != START && \
					((t_room*)rooms->content)->type != END)
			{
				while (room_links)
				{
					link_count++;
					room_links = room_links->next;
				}
				// ft_printf("links for room %s: %d\n", ((t_room*)rooms->content)->name, link_count);
				if (link_count < 2)
				{
					// ft_printf("LINK COUNT < 2\n");
					// t_list *lst;
					// for (lst = lem->link_list; lst; lst = lst->next)
					// 	ft_printf("BEF PTRS: %p\n", lst);
					room_links = ((t_room*)rooms->content)->links;
					if (room_links)
					{
						if (!(room2 = find_room(((t_link*)room_links->content)->room2, lem)))
							ft_exit(RED"ERROR: no room found"RESET);
						// t_list *rooms_lst;
						// for (rooms_lst = room2->links; rooms_lst; rooms_lst = rooms_lst->next)
						// 	ft_printf(YELLOW"LINK IN ROOM BEF: room1: %s room2: %s\n"RESET, ((t_link*)rooms_lst->content)->room1, ((t_link*)rooms_lst->content)->room2);
						link_list_remove(&(lem->link_list), ((t_room*)rooms->content), room2);
						// for (rooms_lst = room2->links; rooms_lst; rooms_lst = rooms_lst->next)
						// 	ft_printf(YELLOW"LINK IN ROOM AFT: room1: %s room2: %s\n"RESET, ((t_link*)rooms_lst->content)->room1, ((t_link*)rooms_lst->content)->room2);
					}
					remove_room(&(lem->room_list), ((t_room*)rooms->content));
					rooms->content = NULL;
					new_loop = 1;
					// for (lst = lem->link_list; lst; lst = lst->next)
					// 	ft_printf("AFT PTRS: %p\n", lst);
				}
			}
			rooms = rooms->next;
		}
	}
}