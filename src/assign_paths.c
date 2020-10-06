/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:36:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/06 17:00:25 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// void    	assign_paths(t_lem *lem, t_room *start)
// {
// 	t_list	*ants;
// 	t_list	*paths;
// 	t_list	*prev_paths;
// 	t_path	*cur_path;
// 	int		starting_ants;
// 	int		decider;

// 	ants = lem->ants;
// 	paths = lem->paths_list;
// 	starting_ants = start->has_ant;
// 	decider = 0;
// 	while (ants)
// 	{
// 		// ft_printf(CYAN"\nAssigning path for ant id: %d\n"RESET, ((t_ant*)ants->content)->id);
// 		if (!paths)
// 			paths = lem->paths_list;
// 		prev_paths = lem->paths_list;
// 		cur_path = (t_path*)paths->content;
// 		// ft_printf(YELLOW"Current path is %la, length: %d\n"RESET, cur_path->path_arr, cur_path->len);
// 		while (prev_paths && prev_paths != paths)
// 		{
// 			// ft_printf(GREEN"Decider: %d, cur_path len: %d - prev len : %d is %d, TOTAL NEW DECIDER = ", decider, cur_path->len, ((t_path*)prev_paths->content)->len, cur_path->len - ((t_path*)prev_paths->content)->len);
// 			decider += cur_path->len - ((t_path*)prev_paths->content)->len;
// 			// ft_printf("%d\n"RESET, decider);
// 			prev_paths = prev_paths->next;
// 		}
// 		// ft_printf(BLUE"STARTING ANTS: %d > DECIDER: %d ?\n"RESET, starting_ants, decider);
// 		if (starting_ants > decider)
// 		{
// 			((t_ant*)ants->content)->path = cur_path;
// 			starting_ants--;
// 			paths = paths->next;
// 			ants = ants->next;
// 		}
// 		else
// 		{
// 			paths = lem->paths_list;
// 			decider = 0;
// 		}
// 	}
// }

static int	max_flow(t_lem *lem)
{
	t_list	*links;
	int		start_links;
	int		end_links;

	start_links = 0;
	end_links = 0;
	links = lem->start->links;
	while (links)
	{
		start_links++;
		links = links->next;
	}
	links = lem->end->links;
	while (links)
	{
		end_links++;
		links = links->next;
	}
	return (min_3(lem->ant_nb, start_links, end_links));
}

static int	*get_steps(t_lem *lem, int *total)
{
	int		*steps;
	t_list	*paths;
	int		i;

	if (!(steps = (int*)malloc(sizeof(int) * lem->max_flow)))
		ft_exit(RED"ERROR: malloc error"RESET);
	paths = lem->paths_list;
	i = 0;
	while (i < lem->max_flow)
	{
		steps[i] = ((t_path*)paths->content)->len;
		total[0] += steps[i];
		i++;
		paths = paths->next;
	}
	return (steps);
}

static int	*calc_div(t_lem *lem, int *divide, int total, int *steps)
{
	int i;

	i = 0;
	total = (total + lem->ant_nb) / lem->max_flow;
	while (i < lem->max_flow)
	{
		divide[i] = total - steps[i];
		i++;
	}
	return(divide);
}

static int	find_longest(int *division, int *steps, int max)
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

static int	*split_remainder(int *ant_division, int remainder, t_lem *lem, int **longest)
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
		division = split_remainder(division, lem->ant_nb - total, lem, &longest);
	return (division);
}

static void	paths_to_ants(t_lem *lem, int *division)
{
	t_list	*paths;
	t_list	*ants;
	int		i;
	// int		j;

	ft_printf("division arr:\n");
	for (int i = 0; i < lem->max_flow; i++)
		ft_printf("division[%d]: %d\n", i, division[i]);
	paths = lem->paths_list;
	ants = lem->ants;
	i = 0;
	while (ants)
	{
		if (division[i] > 0)
		{
			((t_ant*)ants->content)->path = ((t_path*)paths->content);
			ants = ants->next;
			division[i]--;
		}
		// while (j > 0 && ants)
		// {
		// 	((t_ant*)ants->content)->path = ((t_path*)paths->content);
		// 	ants = ants->next;
		// 	j--;
		// }
		if (++i >= lem->max_flow)
			i = 0;
		if (!(paths = paths->next))
			paths = lem->paths_list;
	}

	// while (1) ;
}

void    	assign_paths(t_lem *lem)
{
	int *division;
	int	*steps;
	int total;
	int longest;

	total = 0;
	lem->max_flow = max_flow(lem);
	ft_printf("max flow: %d\n", lem->max_flow);
	if (!(division = (int*)malloc(sizeof(int) * lem->max_flow)))
		ft_exit(RED"ERROR: malloc error"RESET);
	steps = get_steps(lem, &total);
	division = calc_div(lem, division, total, steps);
	longest = find_longest(division, steps, lem->max_flow);
	division = check_total(division, lem, &longest);
	longest = find_longest(division, steps, lem->max_flow);
	ft_memdel((void*)&steps);
	ft_printf("longest: %d\n", longest);
	paths_to_ants(lem, division);
}