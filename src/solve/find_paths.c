/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 16:08:35 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void		reset_rooms_bfs(t_lem *lem)
{
	t_list	*tmp;
	t_room	*room;

	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->visited = FALSE;
		tmp = tmp->next;
	}
}

void		reset_rooms_ek(t_lem *lem)
{
	t_list	*tmp;
	t_room	*room;

	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->visited_ek = FALSE;
		tmp = tmp->next;
	}
}

static void	new_best_set(t_lem *lem)
{
	if (lem->best_set)
		free_set(&lem->best_set);
	lem->best_set = init_set();
	lem->best_set->cost = lem->ek_set->cost;
	lem->best_set->flow = lem->ek_set->flow;
	lem->best_set->len = lem->ek_set->len;
	lem->best_set->paths = lem->ek_set->paths;
}

static int	bfs_loop(t_lem *lem, t_room **path)
{
	if (!path)
		return (1);
	lem->path_amount++;
	assign_flows(path);
	flows_pathfinder(lem);
	if (lem->ek_set->paths)
	{
		sort_paths(lem->ek_set->paths);
		lem->ek_set->cost = ((lem->ek_set->len + lem->ant_nb) \
						/ lem->ek_set->flow) - 1;
		if (lem->best_set == NULL || lem->best_set->cost > lem->ek_set->cost)
			new_best_set(lem);
		else
			free_set(&lem->ek_set);
	}
	reset_rooms_bfs(lem);
	ft_memdel((void**)&path);
	return (0);
}

void		find_paths(t_lem *lem)
{
	t_room	**path;

	while ((path = bfs(lem)) || TRUE)
		if (bfs_loop(lem, path) == 1)
			break ;
	if (!lem->best_set)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts.paths)
		print_paths(lem, lem->best_set->paths);
}
