/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/22 17:49:41 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"
// #include <time.h>


int	main(int argc, char **argv)
{
	t_lem	*lem;
	// clock_t begin;
	// clock_t end;
	// double time;
	lem = lem_init(argc, argv);
	// while (1);
	if (lem->opts.debug)
		debug_out(lem);
	// begin = clock();
	guide_ants(lem);
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf(RED"TIME FOR GUIDE_ANTS: %lf\n"RESET, time);
	if (lem->opts.lines)
		ft_printf("%s%slines: %d\n"RESET, BOLD, GREEN, lem->moves_count);
	return (0);
}
