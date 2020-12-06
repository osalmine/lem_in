/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 18:33:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/03 22:55:33 by osalmine         ###   ########.fr       */
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
	ft_printf("lem_init, lem: %p\n", lem);
	if (sizeof(t_lem) == 16)
		ft_printf(RED"lem_init: SIZEOF T_LEM IS 16\n"RESET);
	lem->ants = NULL;
	lem->link_list = NULL;
	lem->room_list = NULL;
	lem->paths_list = NULL;
	lem->paths_bef_ek = NULL;
	lem->moves_count = 0;
	if (!(lem->opts = (t_opts*)malloc(sizeof(t_opts))))
		ft_exit(RED"Malloc error"RESET);	
	ft_printf("lem_init, lem->opts: %p\n", lem->opts);
	if (sizeof(t_opts) == 16)
		ft_printf(RED"lem_init: SIZEOF T_OPTS IS 16\n"RESET);
	lem_flags(lem, ac, av);
	lem_read(lem);
	add_room_id(lem);
	if (!(lem->start = find_room_by_type(START, lem)))
		ft_exit(RED"ERROR: starting room not found"RESET);
	if (!(lem->end = find_room_by_type(END, lem)))
		ft_exit(RED"ERROR: ending room not found"RESET);
	init_ants(lem);
	// remove_dead_ends(lem);

	// clock_t end = clock();
	// double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

	// ft_printf("Time measeured for init: %.3f seconds.\n", elapsed);

	return (lem);
}
