/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 12:21:45 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int	main(int argc, char **argv)
{
	t_lem	*lem;

	lem = lem_init(argc, argv);
	if (lem->opts->debug)
		debug_out(lem);
	guide_ants(lem);
	if (lem->opts->lines)
		ft_printf("%s%slines: %d\n"RESET, BOLD, GREEN, lem->moves_count);
	free_lem(lem);
	return (0);
}
