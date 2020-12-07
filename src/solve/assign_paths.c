/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:36:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/06 21:13:47 by osalmine         ###   ########.fr       */
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

int			max_flow(t_lem *lem)
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
	// ft_printf("get_steps, steps: %p\n", steps);
	// if (sizeof(int) * lem->max_flow == 16)
	// 	ft_printf(RED"get_steps: SIZEOF sizeof(int) * lem->max_flow IS 16\n"RESET);
	paths = lem->paths_list;
	i = 0;
	while (paths && i < lem->max_flow)
	{
		steps[i] = ((t_path*)paths->content)->len;
		// ft_printf("PATH ARR: %la\n", ((t_path*)paths->content)->path_arr);
		total[0] += steps[i];
		i++;
		paths = paths->next;
		// ft_printf("PATH NEXT PTR: %p\n", paths);
	}
	// while (i < lem->max_flow && !paths)
	// 	steps[i++] = -1;
	// steps[lem->max_flow] = -1;
	return (steps);
}

static int	*calc_div(t_lem *lem, int *divide, int total, int *steps)
{
	int i;

	i = 0;
	total = (total + lem->ant_nb) / lem->max_flow;
	// for (int j = 0; j <= lem->max_flow; j++)
	// 		ft_printf("steps[%d]: %d\n", j, steps[j]);
	while (i < lem->max_flow)
	{
		// if (steps[i] < 0)
		// {
		// 	divide[i] = -1;
		// 	break ;
		// }
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

static void	paths_to_ants(t_lem *lem, int *division, int max)
{
	t_list	*paths;
	t_list	*ants;
	int		i;

	// ft_printf("division arr:\n");
	// for (int j = 0; j < max; j++)
	// 	ft_printf("division[%d]: %d\n", j, division[j]);
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
		if (++i >= max)
			i = 0;
		if (!(paths = paths->next) || i == 0)
			paths = lem->paths_list;
	}
}

// static int	*ft_intarrcpy(int *src, int size)
// {
// 	int *dst;
// 	int i;

// 	if (!(dst = (int*)malloc(sizeof(int) * size)))
// 			ft_exit(RED"ERROR: malloc error"RESET);
// 	i = 0;
// 	while (i < size)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	return (dst);
// }

void    	assign_paths(t_lem *lem)
{
	int *division;
	int	*tmp_div;
	int	*steps;
	int total;
	int longest;
	int i;
	int	div_sum;
	int max;
	int	assign_max;
	t_list *paths;
	int paths_count;

	// lem->max_flow = max;
	max = max_flow(lem);
	// ft_printf("max flow for graph: %d\n", max);
	i = 0;
	division = NULL;
	div_sum = 0;
	assign_max = 0;
	paths = lem->paths_list;
	paths_count = 0;
	while (paths)
	{
		paths_count++;
		paths = paths->next;
	}
	if (paths_count < max)
		max = paths_count;
	while (i++ < max)
	{
		lem->max_flow = i;
		total = 0;
		if (!(tmp_div = (int*)malloc(sizeof(int) * i)))
			ft_exit(RED"ERROR: malloc error"RESET);
		// ft_printf("assign_paths, tmp_div: %p\n", tmp_div);
		// if (sizeof(int) * i == 16)
		// 	ft_printf(RED"assign_paths: sizeof(int) * i IS 16\n"RESET);
		steps = get_steps(lem, &total);
		tmp_div = calc_div(lem, tmp_div, total, steps);
		// for (int j = 0; j < i; j++)
		// 	ft_printf("tmp_div[%d]: %d\n", j, tmp_div[j]);
		longest = find_longest(tmp_div, steps, i);
		tmp_div = check_total(tmp_div, lem, &longest);
		longest = find_longest(tmp_div, steps, i);
		// ft_printf("max flow: %d\n", i);
		// ft_printf("longest: %d\n", longest);
		// ft_printf("division arr:\n");
		// for (int j = 0; j < i; j++)
		// 	ft_printf("division[%d]: %d\n", j, tmp_div[j]);
		longest = -1;
		total = 0;
		while (++longest < i)
			if (tmp_div[longest] > 0)
				total += tmp_div[longest];
		// ft_printf(BLUE"THIS ROUND TOTAL: %d\n"RESET, total);
		// ft_printf(YELLOW"DIV_SUM: %d, ANT NB: %d\n"RESET, div_sum, lem->ant_nb);
		// ft_printf(RED"FT_ABS(ant_nb - div_sum) + 3 = %d, FT_ABS(ant_nb - total) = %d\n"RESET, ft_abs(lem->ant_nb - div_sum) + 3, ft_abs(lem->ant_nb - total));
		if (division == NULL || ft_abs(lem->ant_nb - div_sum) + 3 >= ft_abs(lem->ant_nb - total))
		{
			ft_memdel((void*)&division);
			// ft_printf(CYAN"ASSIGN NEW DIVISION\n"RESET);
			// division = ft_intarrcpy(tmp_div, i);
			// free(tmp_div);
			division = tmp_div;
			div_sum = total;
			assign_max = i;
		}
		else
			free(tmp_div);
		ft_memdel((void*)&steps);
	}
	paths_to_ants(lem, division, assign_max);
}