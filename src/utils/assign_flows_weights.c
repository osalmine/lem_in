/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_flows_weights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:16:35 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/10 19:56:43 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void	assign_weights(t_lem *lem, t_room **path)
{
	int		i;
	t_room	*room;

	i = 0;
	// ft_printf("PATH IN ASSIGN_WEIGHTS: %la\n", path);
	while (path[i])
	{
		if (!(room = find_room(path[i]->name, lem)))
			ft_exit(RED"ERROR: room not found"RESET);
		// ft_printf("ASSIGN WEIGHTS ROOM: %s", room->name);
		if (room->type == END)
			room->weight = INF;
		// else if (room->weight > i)
		// 	room->weight = i;
		else
			room->weight = i;
		// ft_printf(", WEIGHT: %d\n", room->weight);
		i++;
	}
}

void	assign_flows(t_room **path)
{
	int		i;
	t_link	*link;

	i = 0;
	// ft_printf(RED BOLD"NEW ASSIGN\n"RESET);
	while (path[i + 1])
	{
		// ft_printf("path[%d]: %s, path[%d + 1]: %s\n", i, path[i], i, path[i + 1]);
		if (!(link = find_link(path[i], path[i + 1])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		// ft_printf("Link (%s-%s) flow prev assign: %d, ptr: %p\n", link->room1->name, link->room2->name, link->flow, link);
		if (link->flow == INF)
			link->flow = 1;
		else
			link->flow++;
		// ft_printf("Link (%s-%s) flow after assign: %d\n", link->room1->name, link->room2->name, link->flow);
		if (!(link = find_link(path[i + 1], path[i])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		// ft_printf("Link (%s-%s) flow prev assign: %d, ptr: %p\n", link->room1->name, link->room2->name, link->flow, link);
		if (link->flow == INF)
			link->flow = -1;
		else
			link->flow--;
		// ft_printf("Link (%s-%s) flow after assign: %d\n", link->room1->name, link->room2->name, link->flow);
		i++;
	}
}