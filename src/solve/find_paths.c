/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/21 19:16:44 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void	reset_rooms(t_lem *lem)
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

void        find_paths(t_lem *lem, t_room *start, t_room *end)
{
    char	**path;
	// t_path	*path_struct;

	start->weight = 0;
	while ((path = bfs(start, end, lem)))
	{
		if (!path || check_for_dup_path(lem->paths_bef_ek, path))
			break ;
		assign_weights(lem, path);
		assign_flows(lem, path);
		ft_printf(BOLD YELLOW"Path returned from BFS: %la\n\n"RESET, path);
		if (lem->ant_nb == 1)
		{
			add_path(lem, path, &(lem->paths_list));
			// ft_printf("added path to paths_list, ptr: %p\n", lem->paths_list);
			free_strsplit(&path);
			break ;
		}
		else
		{
			add_path(lem, path, &(lem->paths_bef_ek));
		}
		// t_list *pths;
		// pths = lem->paths_bef_ek;
		// while (pths)
		// {
		// 	ft_printf("PATH IN PATHS_BEF_EK: %la, IN USE: %d\n", ((t_path*)pths->content)->path_arr, ((t_path*)pths->content)->in_use);
		// 	pths = pths->next;
		// }
		reset_rooms(lem);
	}
	// t_list *links;
	// t_link *link;
	// links = lem->link_list;
	// while (links)
	// {
	// 	link = (t_link*)links->content;
	// 	ft_printf("LINK: room1: %s, room2: %s, flow: %d\n", link->room1, link->room2, link->flow);
	// 	links = links->next;
	// }
	// ft_printf("lem->ant_nb: %d\n", lem->ant_nb);
	if (lem->ant_nb != 1)
		flows_pathfinder(lem);
	sort_paths(lem);
	// ft_printf(RED BOLD UNDERLINE"FOUND ALL PATHS\n"RESET);
	if (!lem->paths_list)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts->paths)
		print_paths(lem);
}