/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 18:33:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/07 19:02:34 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// #include <time.h>

static void  add_room_id(t_lem* lem)
{
	int		id;
	t_list	*tmp;
	t_room	*room;

	id = 0;
	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->id = id;
		id++;
		tmp = tmp->next;
	}
}

t_lem	*lem_init(int ac, char **av)
{
	t_lem *lem;

	// clock_t start = clock();

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_exit(RED"Malloc error"RESET);
	lem->ants = NULL;
	lem->link_list = NULL;
	lem->room_list = NULL;
	lem->paths_list = NULL;
	lem->paths_bef_ek = NULL;
	lem->moves_count = 0;
	if (!(lem->opts = (t_opts*)malloc(sizeof(t_opts))))
		ft_exit(RED"Malloc error"RESET);
	lem_flags(lem, ac, av);
	lem_read(lem);
	if (!(lem->start = find_room_by_type(START, lem)))
		ft_exit(RED"ERROR: starting room not found"RESET);
	if (!(lem->end = find_room_by_type(END, lem)))
		ft_exit(RED"ERROR: ending room not found"RESET);
	init_ants(lem);
	// remove_dead_ends(lem);
	add_room_id(lem);
	lem->room_nb = room_count(lem);
	create_room_table(lem);
	create_link_table(lem);

	// clock_t end = clock();
	// double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

	// ft_printf("Time measeured for init: %.3f seconds.\n", elapsed);

	return (lem);
}
