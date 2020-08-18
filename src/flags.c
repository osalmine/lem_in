/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:36:00 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/17 16:23:06 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	display_help(void)
{
	ft_exit("Help message for lem_in. -d (--debug) flag is for debug, -h (--help) is to see this.");
}

void		lem_flags(t_lem *lem, int ac, char **av)
{
	int i;
	int j;

	i = 0;
	while (--ac > 0)
	{
		i++;
		if (ft_strequ(av[i], "--help"))
			display_help();
		else if (ft_strequ(av[i], "--debug"))
			lem->opts->debug = TRUE;
		else if (av[i][0] == '-')
		{
			j = 1;
			while (av[i][j] && !ft_isblank(av[i][j]))
			{
				if (av[i][j] == 'd')
				{
					lem->opts->debug = TRUE;
				}
				else if (av[i][j] == 'h')
					display_help();
				else
				{
					ft_fprintf(2, "Unknown option %s, please refer to %s -h for help\n", \
																		av[i], av[0]);
					exit(1);
				}
				j++;
			}
		}
	}
}
