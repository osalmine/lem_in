/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/03 01:23:06 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void			guide_ants(t_lem *lem)
{
	find_paths(lem);
	assign_paths(lem);
	while (lem->end->has_ant != lem->ant_nb)
		turn_loop(lem);
}
