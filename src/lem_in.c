/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:44 by osalmine          #+#    #+#             */
/*   Updated: 2020/03/19 21:22:21 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_lem *lem;

	lem = lem_init(argc, argv);
	printf("Ok\n");
	if (argc > 0)
		ft_printf("ARGV: %a\n", argv);
	return (0);
}
