/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 14:42:58 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/13 16:04:02 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int		*get_steps(t_lem *lem, int *total)
{
	int		*steps;
	t_list	*paths;
	int		i;

	if (!(steps = (int*)malloc(sizeof(int) * lem->max_flow)))
		ft_exit(RED"ERROR: malloc error"RESET);
	paths = lem->best_set->paths;
	i = 0;
	while (paths && i < lem->max_flow)
	{
		steps[i] = ((t_path*)paths->content)->len;
		total[0] += steps[i];
		i++;
		paths = paths->next;
	}
	return (steps);
}

int		*calc_div(t_lem *lem, int *divide, int total, int *steps)
{
	int i;

	i = 0;
	total = (total + lem->ant_nb) / lem->max_flow;
	while (i < lem->max_flow)
	{
		divide[i] = total - steps[i];
		i++;
	}
	return (divide);
}

int		find_longest(int *division, int *steps, int max)
{
	int i;
	int longest;

	i = 0;
	longest = 0;
	while (i < max)
	{
		if (longest < steps[i] + division[i] - 1)
			longest = steps[i] + division[i] - 1;
		i++;
	}
	return (longest);
}

int		*split_remainder(int *ant_division, int remainder, \
						t_lem *lem, int **longest)
{
	int		i;
	int		full;

	full = 0;
	while (remainder > 0)
	{
		i = 0;
		while (i < lem->max_flow)
		{
			if (ant_division[i] + 1 <= **longest)
			{
				remainder--;
				ant_division[i]++;
			}
			if (ant_division[i] >= **longest)
				full++;
			if (full == lem->max_flow)
			{
				full = 0;
				(**longest)++;
			}
			i++;
		}
	}
	return (ant_division);
}

void	paths_to_ants(t_lem *lem, int *division, int max)
{
	t_list	*paths;
	t_list	*ants;
	int		i;

	paths = lem->best_set->paths;
	ants = lem->ants;
	i = 0;
	if (!paths || !division)
		ft_exit(RED"ERROR: no paths or division"RESET);
	while (ants)
	{
		if (division[i] > 0)
		{
			((t_ant*)ants->content)->path = ((t_path*)paths->content);
			ants = ants->next;
			division[i]--;
		}
		if (++i >= max)
			i = 0;
		if (!(paths = paths->next) || i == 0)
			paths = lem->best_set->paths;
	}
	ft_memdel((void*)&division);
}
