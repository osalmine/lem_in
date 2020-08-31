/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:36:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/31 15:25:44 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void    assign_paths(t_lem *lem, t_room *start)
{
	t_list	*ants;
	t_list	*paths;
	t_list	*prev_paths;
	t_path	*cur_path;
	// t_path	*prev_path;
	int		starting_ants;
	int		decider;

	ants = lem->ants;
	paths = lem->paths_list;
	starting_ants = start->has_ant;
	decider = 0;
	// ft_printf("Starting ants beginning: %d\n", starting_ants);
	while (ants)
	{
		if (!paths)
			paths = lem->paths_list;
		// ft_printf("Ok\n");
		prev_paths = lem->paths_list;
		cur_path = (t_path*)paths->content;
		while (prev_paths && prev_paths != paths)
		{
			decider += cur_path->len - ((t_path*)prev_paths->next)->len;
			prev_paths = prev_paths->next;
		}
		if (starting_ants > decider)
		{
			((t_ant*)ants->content)->path = cur_path;
			starting_ants--;
			paths = paths->next;
			ants = ants->next;
			// ft_printf("Starting ants: %d\n", starting_ants);
		}
		else
			paths = lem->paths_list;
	}
}