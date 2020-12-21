/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 11:06:08 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void		ft_push_to(t_room ****path, int i, t_room *push_to)
{
	if (push_to)
	{
		find_link((**path)[i], push_to)->flow = INF;
		push_to_room_arr(**path, push_to);
		push_to = NULL;
	}
}

static void		ek_loop(t_lem *lem, int i, t_room **current, t_room ***path)
{
	t_room	*push_to;
	t_room	*next;
	t_list	*links;

	push_to = NULL;
	reset_rooms(lem);
	links = (*current)->links;
	while (links)
	{
		if (((t_link*)links->content)->flow == 1)
		{
			next = ((t_link*)links->content)->room2;
			if (!next->visited && \
				!find_in_path(lem->paths_list, next, lem->end))
			{
				(*current) = next;
				(*current)->visited = TRUE;
				push_to = *current;
				if (next->type == END)
					break ;
			}
		}
		links = links->next;
	}
	ft_push_to(&path, i, push_to);
}

static t_room	**ek_find_path(t_lem *lem)
{
	t_room	**path;
	t_room	*current;
	int		i;

	i = 0;
	path = create_room_arr(lem, -1);
	current = lem->start;
	push_to_room_arr(path, current);
	current->visited = TRUE;
	while (path[i] && lem->end != path[i])
	{
		ek_loop(lem, i, &current, &path);
		i++;
	}
	if (path[room_arr_size(path) - 1] == lem->end \
		&& !check_for_dup_path_size_1(lem, path))
		return (path);
	i = lem->room_count;
	ft_memdel((void*)&path);
	return (NULL);
}

void			flows_pathfinder(t_lem *lem)
{
	t_room	**path;
	int		i;

	i = 0;
	lem->max_flow = max_flow(lem);
	while ((path = ek_find_path(lem)) || i++ < lem->max_flow)
		if (path)
			add_path(lem, path, &(lem->paths_list));
}
