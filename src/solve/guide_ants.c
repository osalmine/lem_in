/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/13 21:34:39 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// static void		compare_paths(t_lem *lem)
// {
// 	int		len;
// 	int		len2;
// 	int		pathnb;
// 	int		pathnb2;
// 	int		cost;
// 	int		cost2;
// 	t_list	*pth;

// 	len = 0;
// 	len2 = 0;
// 	pth = lem->paths_list;
// 	pathnb = 0;
// 	// ft_printf("PATHS1\n");
// 	while (pth)
// 	{
// 		// ft_printf("room[1]: %s\n", ((t_path*)pth->content)->path_arr[1]->name);
// 		len += ((t_path*)pth->content)->len;
// 		pathnb++;
// 		pth = pth->next;
// 	}
// 	cost = ((len + lem->ant_nb) / get_max(lem, lem->paths_list)) - 1;
// 	pth = lem->paths_list2;
// 	pathnb2 = 0;
// 	// ft_printf("PATHS2\n");
// 	while (pth)
// 	{
// 		// ft_printf("room[1]: %s\n", ((t_path*)pth->content)->path_arr[1]->name);
// 		len2 += ((t_path*)pth->content)->len;
// 		pathnb2++;
// 		pth = pth->next;
// 	}
// 	// ft_printf("len: %d, len2: %d\n", len, len2);
// 	cost2 = ((len2 + lem->ant_nb) / get_max(lem, lem->paths_list2)) - 1;
// 	ft_printf(BOLD CYAN"COST1: %d, COST2: %d\n"RESET, cost, cost2);
// 	if (cost2 < cost)
// 	{
// 		ft_printf(BOLD YELLOW"SELECT SECOND PATH\n"RESET);
// 		lem->paths_list = lem->paths_list2;
// 	}
// 	// lem->paths_list = lem->paths_list2;
// }

// static void		hard_reset_rooms(t_lem *lem)
// {
// 	t_list	*tmp;
// 	t_room	*room;

// 	tmp = lem->room_list;
// 	while (tmp)
// 	{
// 		room = (t_room*)tmp->content;
// 		room->visited = FALSE;
// 		room->weight = INF - 1;
// 		room->in_path = FALSE;
// 		tmp = tmp->next;
// 	}
// 	tmp = lem->link_list;
// 	// go through links only in path
// 	while (tmp)
// 	{
// 		((t_link*)tmp->content)->flow = INF;
// 		tmp = tmp->next;
// 	}
// }

// static void		init_sets_list(t_lem *lem)
// {
// 	lem->sets_list = NULL;
// }

void			guide_ants(t_lem *lem)
{
	// init_sets_list(lem);
	find_paths(lem, 1);
	// if (lem->ant_nb > 1)
	// {
	// 	// ft_printf(BOLD GREEN"\nFINDING SECOND SET\n\n\n"RESET);
	// 	hard_reset_rooms(lem);
	// 	find_paths(lem, 2);
	// 	compare_paths(lem);
	// }
	assign_paths(lem);
	while (lem->end->has_ant != lem->ant_nb)
		turn_loop(lem);
}
