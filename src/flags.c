/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:36:00 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/01 09:47:35 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	display_help(void)
{
	ft_exit("Help message for lem-in. -d (--debug) flag is for debug, -l (--lines) is to see output line count, -p (--paths) to see the paths, -h (--help) is to see this.");
}

static void	dash_flags(t_lem *lem, char **av, int i)
{
	int j;

	j = 1;
	while (av[i][j] && !ft_isblank(av[i][j]))
	{
		if (av[i][j] == 'd')
			lem->opts->debug = TRUE;
		else if (av[i][j] == 'l')
			lem->opts->lines = TRUE;
		else if (av[i][j] == 'p')
			lem->opts->paths = TRUE;
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

void		lem_flags(t_lem *lem, int ac, char **av)
{
	int i;

	lem->opts->debug = FALSE;
	lem->opts->lines = FALSE;
	lem->opts->paths = FALSE;
	i = 1;
	while (--ac > 0)
	{
		if (ft_strequ(av[i], "--help"))
			display_help();
		else if (ft_strequ(av[i], "--debug"))
			lem->opts->debug = TRUE;
		else if (ft_strequ(av[i], "--lines"))
			lem->opts->lines = TRUE;
		else if (ft_strequ(av[i], "--paths"))
			lem->opts->paths = TRUE;
		else if (av[i][0] == '-')
			dash_flags(lem, av, i);
		// else
		// {
		// 	ft_fprintf(2, "Unknown option %s, please refer to %s -h for help\n", \
		// 														av[i], av[0]);
		// 	exit(1);
		// }
		i++;
	}
}
