/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 11:12:31 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void		reset_rooms(t_lem *lem)
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

static int	bfs_loop(t_lem *lem, t_room **path)
{
	if (!path || check_for_dup_path(lem->paths_bef_ek, path))
	{
		ft_printf(RED"Freeing path\n"RESET);
		if (path)
			free(path);
		return (1);
	}
	assign_weights(lem, path);
	assign_flows(path);
	if (lem->ant_nb == 1)
	{
		add_path(lem, path, &(lem->paths_list));
		return (1);
	}
	else
		add_path(lem, path, &(lem->paths_bef_ek));
	reset_rooms(lem);
	return (0);
}

void		find_paths(t_lem *lem)
{
	t_room	**path;
	int		breaking;

	lem->start->weight = 0;
	while ((path = bfs(lem)))
	{
		if ((breaking = bfs_loop(lem, path)) == 1)
			break ;
	}
	if (lem->ant_nb != 1)
		flows_pathfinder(lem);
	sort_paths(lem);
	if (!lem->paths_list)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts->paths)
		print_paths(lem);
}
