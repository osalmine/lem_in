/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 18:33:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/18 22:42:19 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_lem	*lem_init(int ac, char **av)
{
	t_lem *lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_exit("Malloc error\n");
	if (!(lem->ants = (t_list*)malloc(sizeof(t_list))))
		ft_exit("Malloc error\n");
	if (!(lem->room_list = (t_list*)malloc(sizeof(t_list))))
		ft_exit("Malloc error\n");
	if (!(lem->opts = (t_opts*)malloc(sizeof(t_opts))))
		ft_exit("Malloc error\n");
	lem_flags(lem, ac, av);
	lem_read(lem);
	return (lem);
}
