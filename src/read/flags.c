/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:36:00 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/30 12:44:18 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	display_help(void)
{
	ft_exit("Example usages:\n\\t./lem-in < big.map\n\t./lem-in -plc < test.map\
\n\techo map | ./lem-in -dl\n\nMore info in GitHub repo\
\nFlags:\n\t-d (--debug) \
flag is for debug\n\t-l (--lines) is to see output line count\n\t\
-p (--paths) to see the paths\n\t-c (--colours, --colors) \
to see paths in colours\n\t-h (--help) is to see this\n");
}

static void	dash_flags(t_lem *lem, char **av, int i)
{
	int j;

	j = 1;
	while (av[i][j] && !ft_isblank(av[i][j]))
	{
		if (av[i][j] == 'd')
			lem->opts.debug = TRUE;
		else if (av[i][j] == 'l')
			lem->opts.lines = TRUE;
		else if (av[i][j] == 'p')
			lem->opts.paths = TRUE;
		else if (av[i][j] == 'c')
			lem->opts.colours = TRUE;
		else if (av[i][j] == 'h')
			display_help();
		else
		{
			ft_fprintf(2, "Unknown option %s, please \
refer to %s -h for help\n", \
							av[i], av[0]);
			exit(1);
		}
		j++;
	}
}

void		lem_flags(t_lem *lem, int ac, char **av)
{
	int i;

	lem->opts.debug = FALSE;
	lem->opts.lines = FALSE;
	lem->opts.paths = FALSE;
	lem->opts.colours = FALSE;
	i = 1;
	while (--ac > 0)
	{
		if (ft_strequ(av[i], "--help"))
			display_help();
		else if (ft_strequ(av[i], "--debug"))
			lem->opts.debug = TRUE;
		else if (ft_strequ(av[i], "--lines"))
			lem->opts.lines = TRUE;
		else if (ft_strequ(av[i], "--paths"))
			lem->opts.paths = TRUE;
		else if (ft_strequ(av[i], "--colours") || ft_strequ(av[i], "--colors"))
			lem->opts.colours = TRUE;
		else if (av[i][0] == '-')
			dash_flags(lem, av, i);
		i++;
	}
}
