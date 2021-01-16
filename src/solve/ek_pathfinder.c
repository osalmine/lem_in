/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/16 11:44:50 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void		ft_push_to(t_room ****path, int i, t_room *push_to)
{
	i = 1;
	if (push_to)
	{
		// find_link((**path)[i], push_to)->flow = INF;
		push_to_room_arr(**path, push_to);
		// push_to = NULL;
	}
}

static void		ek_loop(t_lem *lem, int i, t_room **current, t_room ***path)
{
	// t_room	*push_to;
	t_room	*next;
	t_list	*links;
	t_list	*paths;

	// push_to = NULL;
	// reset_rooms_ek(lem);
	(*current)->visited_ek = TRUE;
	links = (*current)->links;
	// if (nb == 1)
	// if (!lem->cur_set)
	// 	init_set(lem);
	// if (lem->ek_set)
		paths = lem->ek_set->paths;
	// else
	// 	paths = NULL;
	// t_list *rooms;
	// rooms = lem->room_list;
	// while (rooms)
	// {
	// 	if (((t_room*)rooms->content)->visited_ek == 1)
	// 		ft_printf(BOLD RED"NAME: %s, VISISTED: %d\n"RESET, ((t_room*)rooms->content)->name, ((t_room*)rooms->content)->visited_ek);
	// 	rooms = rooms->next;
	// }
	// else
	// 	paths = lem->paths_list2;
	while (links)
	{
		if (((t_link*)links->content)->flow == 1)
		{
			next = ((t_link*)links->content)->room2;
			// if (!next->visited_ek && \
			// 	!find_in_path(paths, next, lem->end))
			if (!next->visited_ek)
			{
				(*current) = next;
				// (*current)->visited_ek = TRUE;
				// push_to = *current;
				ft_push_to(&path, i, (*current));
				// if (next->type == END)
					return ;
			}
		}
		links = links->next;
	}
	// ft_push_to(&path, i, push_to);
}

static t_room	**ek_find_path(t_lem *lem)
{
	t_room	**path;
	t_room	*current;
	int		i;

	i = 0;
	path = create_room_arr(lem);
	current = lem->start;
	push_to_room_arr(path, current);
	while (path[i] && lem->end != path[i])
	// while (current)
	{
		ek_loop(lem, i, &current, &path);
		i++;
	}
	// if (path[room_arr_size(path) - 1] == lem->end \
	// 	&& !check_for_dup_path_size_1(lem, path))
	if (path[room_arr_size(path) - 1] == lem->end)
		return (path);
	// i = lem->room_count;
	ft_memdel((void*)&path);
	return (NULL);
}

void			flows_pathfinder(t_lem *lem)
{
	t_room	**path;
	int		i;

	i = 0;
	// ft_printf(BOLD CYAN"NEW EK SET\n"RESET);
	// lem->max_flow = max_flow(lem);
	// ft_printf("max_flow: %d\n", lem->max_flow);
	ft_memdel((void**)&lem->ek_set);
	reset_rooms_ek(lem);
	// if (!lem->ek_set)
	*(&lem->ek_set) = init_set();
	// while ((path = ek_find_path(lem, nb)) || i++ < lem->max_flow)
	while ((path = ek_find_path(lem)) || i++ < lem->path_amount)
	{
		if (path)
		{
			// ft_printf("ASSIGNING TO PATH1\n");
			add_path(lem, path, &(lem->ek_set->paths), &lem->ek_set);
			lem->ek_set->flow++;
			// ft_printf("lem->ek_set->flow incresed to %d\n", lem->ek_set->flow);
		}
		// if (path && nb == 2)
		// {
		// 	// ft_printf("ASSIGNING TO PATH2\n");
		// 	add_path(lem, path, &(lem->paths_list2), nb);
		// }
	}
}
