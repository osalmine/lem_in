/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 10:30:08 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/06 08:55:45 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static t_ant	*add_ant(int id, t_room *ant_room)
{
	t_ant *ant;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		ft_exit("Malloc error");
	ant->id = id;
	ant->room = ant_room;
	ant->has_moved = FALSE;
	ant->move_nb = 0;
	ant->path = NULL;
	return (ant);
}

void			init_ants(t_lem *lem)
{
	int		i;

	i = 1;
	while (i <= lem->ant_nb)
		ft_lstaddlast(&lem->ants, ft_lstnew(add_ant(i++, lem->start), sizeof(t_ant)));
}