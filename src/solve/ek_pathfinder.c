/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 16:08:30 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void		ek_loop(t_room **current, t_room ***path)
{
	t_room	*next;
	t_list	*links;

	links = (*current)->links;
	while (links)
	{
		if (((t_link*)links->content)->flow == 1)
		{
			next = ((t_link*)links->content)->room2;
			if (!next->visited_ek)
			{
				(*current) = next;
				push_to_room_arr(*path, *current);
				return ;
			}
		}
		links = links->next;
	}
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
	{
		ek_loop(&current, &path);
		i++;
	}
	if (path[room_arr_size(path) - 1] == lem->end)
		return (path);
	ft_memdel((void*)&path);
	return (NULL);
}

static void		mark_visited(t_lem *lem, t_room **path)
{
	int i;

	i = 0;
	while (path[i] && path[i] != lem->end)
	{
		path[i]->visited_ek = TRUE;
		path[i]->in_path = TRUE;
		i++;
	}
}

void			flows_pathfinder(t_lem *lem)
{
	t_room	**path;
	int		i;

	i = 0;
	ft_memdel((void**)&lem->ek_set);
	reset_rooms_ek(lem);
	if (!lem->ek_set)
		*(&lem->ek_set) = init_set();
	while ((path = ek_find_path(lem)) || i++ < lem->path_amount)
	{
		if (path)
		{
			mark_visited(lem, path);
			add_path(lem, path, &(lem->ek_set->paths), &lem->ek_set);
			lem->ek_set->flow++;
			if (lem->ek_set->len == 1)
				return ;
		}
	}
}
