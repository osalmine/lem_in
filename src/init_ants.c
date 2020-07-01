/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 10:30:08 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/01 11:51:11 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static t_ant	*add_ant(int id, t_room *ant_room)
{
	t_ant *ant;

	if (!(ant = (t_ant*)malloc(sizeof(ant))))
		ft_exit("Malloc error");
	ant->id = id;
	ant->room = ant_room;
	ant->has_moved = FALSE;
	return (ant);
}

void			init_ants(t_lem *lem)
{
	int		i;
	t_room	*ant_room;

	i = 0;
	ant_room = find_room_by_type(START, lem);
	while (i < lem->ant_nb)
		ft_lstadd(&lem->ants, ft_lstnew(add_ant(i++, ant_room), sizeof(t_ant)));
}