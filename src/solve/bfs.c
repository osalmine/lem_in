/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:50:08 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 13:53:11 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int		check_flow(t_lem *lem, t_room *current, \
					t_room *next, t_room ***prev)
{
	int		check;
	int		limit;
	t_link	*link;
	t_room	*parent;

	check = 0;
	limit = 1;
	parent = NULL;
	if (!(link = find_link(current, next)))
		ft_exit(RED"ERROR: can't find link (check_for_flow)"RESET);
	if ((*prev)[current->id])
		parent = lem->room_arr[(*prev)[current->id]->id];
	if (parent && current->in_path == TRUE && parent->in_path == FALSE)
		limit = INF;
	if ((link->flow == -1 || link->flow == INF) && link->flow != limit)
		check = 1;
	return (check);
}

static void		solve_loop(t_lem *lem, t_room ***prev, t_room ***que, int i)
{
	int		can_use_link;
	t_room	*node;
	t_room	*neighbor;
	t_list	*tmp;

	node = (*que)[i];
	tmp = node->links;
	while (tmp)
	{
		neighbor = ((t_link*)tmp->content)->room2;
		can_use_link = check_flow(lem, node, neighbor, prev);
		if (!neighbor->visited && can_use_link)
		{
			push_to_room_arr(*que, neighbor);
			neighbor->visited = TRUE;
			(*prev)[neighbor->id] = node;
		}
		tmp = tmp->next;
	}
}

static t_room	**solve(t_lem *lem)
{
	t_room	**prev;
	t_room	**que;
	int		i;

	i = 0;
	que = create_room_arr(lem);
	prev = create_room_arr(lem);
	lem->start->visited = TRUE;
	push_to_room_arr(que, lem->start);
	while (que[i] != NULL)
	{
		solve_loop(lem, &prev, &que, i);
		i++;
	}
	free(que);
	return (prev);
}

static t_room	**reconstruct_path(t_room ***prev, t_lem *lem)
{
	t_room	**path;
	t_room	*current;

	path = create_room_arr(lem);
	current = lem->end;
	while (current != NULL)
	{
		push_to_room_arr(path, current);
		if ((*prev)[current->id] && \
			lem->room_links_arr[current->id][(*prev)[current->id]->id] != -1)
			current = lem->room_arr[lem->room_links_arr\
					[current->id][(*prev)[current->id]->id]];
		else
			current = NULL;
	}
	path = room_arr_reverse(path);
	if (ft_strequ(path[0]->name, lem->start->name))
		return (path);
	free(path);
	return (NULL);
}

t_room			**bfs(t_lem *lem)
{
	t_room	**prev;
	t_room	**path;

	prev = solve(lem);
	path = reconstruct_path(&prev, lem);
	free(prev);
	return (path);
}
