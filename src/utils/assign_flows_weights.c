/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_flows_weights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:16:35 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 11:34:03 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void	assign_weights(t_lem *lem, t_room **path)
{
	int		i;
	t_room	*room;

	i = 0;
	while (path[i])
	{
		if (!(room = find_room(path[i]->name, lem)))
			ft_exit(RED"ERROR: room not found"RESET);
		if (room->type == END)
			room->weight = INF;
		else
			room->weight = i;
		i++;
	}
}

void	assign_flows(t_room **path)
{
	int		i;
	t_link	*link;

	i = 0;
	while (path[i + 1])
	{
		if (!(link = find_link(path[i], path[i + 1])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		if (link->flow == INF)
			link->flow = 1;
		else
			link->flow++;
		if (!(link = find_link(path[i + 1], path[i])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		if (link->flow == INF)
			link->flow = -1;
		else
			link->flow--;
		i++;
	}
}
