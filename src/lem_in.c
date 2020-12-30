/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/31 00:27:40 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"
#include <time.h>


int	main(int argc, char **argv)
{
	t_lem	*lem;
	// clock_t begin;
	// clock_t end;
	// double time;
	lem = lem_init(argc, argv);
	if (lem->opts.debug)
		debug_out(lem);
	// begin = clock();
	guide_ants(lem);
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf(RED"TIME FOR GUIDE_ANTS: %lf\n"RESET, time);
	if (lem->opts.lines)
		ft_printf("%s%slines: %d\n"RESET, BOLD, GREEN, lem->moves_count);
	// t_list *rooms;
	// rooms = lem->room_list;
	// int largest = 0;
	// int hash_nb;
	// while (rooms)
	// {
	// 	hash_nb = hash(((t_room*)rooms->content)->name, lem->room_count * 1.5);
	// 	if (hash_nb > largest)
	// 		largest = hash_nb;
	// 	ft_printf("Hash for room %s : %ld\n", ((t_room*)rooms->content)->name, hash_nb);
	// 	rooms = rooms->next;
	// }
	// ft_printf("Room count (%d) * 1.5: %d, largest: %ld\n", lem->room_count, (int)(lem->room_count * 1.5), largest);
	return (0);
}