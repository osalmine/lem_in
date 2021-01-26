/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:11:08 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 13:59:23 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int		min_3(int x, int y, int z)
{
	if (x < y)
		return (x < z ? x : z);
	else
		return (y < z ? y : z);
}

int		max_flow(t_lem *lem)
{
	t_list	*links;
	int		start_links;
	int		end_links;

	start_links = 0;
	end_links = 0;
	links = lem->start->links;
	while (links)
	{
		start_links++;
		links = links->next;
	}
	links = lem->end->links;
	while (links)
	{
		end_links++;
		links = links->next;
	}
	return (min_3(lem->ant_nb, start_links, end_links));
}
