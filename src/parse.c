/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 20:58:13 by osalmine          #+#    #+#             */
/*   Updated: 2020/03/19 21:21:38 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_lem	*lem_init(int ac, char **av)
{
	t_lem *lem;

	ft_putchar_fd(av[0][0], -1);
	if (ac == -1)
		ac += 1;
	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_exit("Malloc error\n");
	return (lem);
}
