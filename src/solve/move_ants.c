/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:54:28 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/03 01:33:54 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static t_room	*check_for_errors(t_lem *lem, t_ant *cur_ant)
{
	t_room *next_room;

	next_room = NULL;
	if (!cur_ant->path->path_arr[cur_ant->move_nb + 1] \
		|| !cur_ant->path->path_arr[cur_ant->move_nb + 1]->name \
		|| (lem->room_links_arr[cur_ant->path->path_arr \
			[cur_ant->move_nb]->id][cur_ant->path->path_arr \
			[cur_ant->move_nb + 1]->id] != -1 && \
			!(next_room = lem->room_arr[lem->room_links_arr \
			[cur_ant->path->path_arr[cur_ant->move_nb]->id]\
			[cur_ant->path->path_arr[cur_ant->move_nb + 1]->id]])))
		ft_exit(RED"ERROR: room not found (turn_loop)"RESET);
	return (next_room);
}

static void		display_moving_ants(t_lem *lem, t_ant *cur_ant)
{
	if (lem->opts.colours)
	{
		ft_putstr(cur_ant->path->colour);
		ft_putchar('L');
		ft_putnbr(cur_ant->id);
		ft_putchar('-');
		ft_putstr(cur_ant->room->name);
		ft_putchar(' ');
	}
	else
	{
		ft_putchar('L');
		ft_putnbr(cur_ant->id);
		ft_putchar('-');
		ft_putstr(cur_ant->room->name);
		ft_putchar(' ');
	}
}

static void		move_ant(t_lem *lem, t_ant *cur_ant)
{
	t_room	*next_room;

	next_room = check_for_errors(lem, cur_ant);
	if (!next_room->has_ant || next_room->type == END)
	{
		cur_ant->room->has_ant = FALSE;
		cur_ant->room = next_room;
		display_moving_ants(lem, cur_ant);
		if (cur_ant->room->type == NORMAL)
			cur_ant->room->has_ant = TRUE;
		cur_ant->move_nb++;
		if (cur_ant->room->type == END)
			lem->end->has_ant++;
	}
}

void			turn_loop(t_lem *lem)
{
	int		i;
	t_ant	*cur_ant;
	t_list	*ant_list;

	i = 0;
	ant_list = lem->ants;
	while (i < lem->ant_nb)
	{
		cur_ant = (t_ant*)ant_list->content;
		if (cur_ant->room->type != END)
		{
			if (cur_ant->path == NULL && cur_ant->id == 1)
				ft_exit(RED"ERROR: No path found"RESET);
			if (cur_ant->path != NULL)
				move_ant(lem, cur_ant);
		}
		i++;
		ant_list = ant_list->next;
	}
	ft_putchar('\n');
	lem->moves_count++;
}