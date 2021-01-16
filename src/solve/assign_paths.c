/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:36:24 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/13 16:02:27 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int	*check_total(int *division, t_lem *lem, int *longest)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (i < lem->max_flow)
	{
		total = total + division[i];
		i++;
	}
	if (total < lem->ant_nb)
		division = split_remainder(division, \
					lem->ant_nb - total, lem, &longest);
	return (division);
}

int	get_max(t_lem *lem, t_list *lst)
{
	int		max;
	t_list	*paths;
	int		paths_count;

	max = max_flow(lem);
	paths = lst;
	paths_count = 0;
	while (paths)
	{
		paths_count++;
		paths = paths->next;
	}
	if (paths_count < max)
		max = paths_count;
	return (max);
}

static int	assign_div(int i, int *tmp_div, int **division)
{
	int longest;

	longest = -1;
	if (*division == NULL || tmp_div[i - 1] >= 0)
	{
		if (*division != NULL)
			ft_memdel((void*)division);
		*division = tmp_div;
		return (i);
	}
	else
	{
		ft_memdel((void*)&tmp_div);
		return (i - 1);
	}
}

void		assign_paths_loop(t_lem *lem, int i, int **tmp_div)
{
	int total;
	int	*steps;
	int	longest;

	total = 0;
	if (!(*tmp_div = (int*)malloc(sizeof(int) * i)))
		ft_exit(RED"ERROR: malloc error"RESET);
	steps = get_steps(lem, &total);
	*tmp_div = calc_div(lem, *tmp_div, total, steps);
	longest = find_longest(*tmp_div, steps, i);
	*tmp_div = check_total(*tmp_div, lem, &longest);
	ft_memdel((void*)&steps);
}

void		assign_paths(t_lem *lem)
{
	int		*division;
	int		*tmp_div;
	int		i;
	int		max;
	int		assign_max;

	i = 0;
	division = NULL;
	assign_max = 0;
	max = get_max(lem, lem->best_set->paths);
	while (i++ < max)
	{
		lem->max_flow = i;
		assign_paths_loop(lem, i, &tmp_div);
		if ((assign_max = assign_div(i, tmp_div, &division)) == i - 1)
			break ;
	}
	paths_to_ants(lem, division, assign_max);
}
