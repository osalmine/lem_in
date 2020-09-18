/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:36:24 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/14 17:06:18 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void		swap(t_list *a, t_list *b)
{
	void	*content;
	size_t	content_size;

	content = a->content;
	content_size = a->content_size;
	a->content = b->content;
	a->content_size = b->content_size;
	b->content = content;
	b->content_size = content_size;
}

void	sort_paths(t_lem *lem)
{
	t_list *lst;
	t_list *next;

	lst = lem->paths_list;
	while (lst)
	{
		next = lst;
		while (next)
		{
			if (((t_path*)next->content)->len < ((t_path*)lst->content)->len)
				swap(next, lst);
			next = next->next;
		}
		lst = lst->next;
	}
}

void    	assign_paths(t_lem *lem, t_room *start)
{
	t_list	*ants;
	t_list	*paths;
	t_list	*prev_paths;
	t_path	*cur_path;
	int		starting_ants;
	int		decider;

	ants = lem->ants;
	paths = lem->paths_list;
	starting_ants = start->has_ant;
	decider = 0;
	while (ants)
	{
		// ft_printf(CYAN"\nAssigning path for ant id: %d\n"RESET, ((t_ant*)ants->content)->id);
		if (!paths)
			paths = lem->paths_list;
		prev_paths = lem->paths_list;
		cur_path = (t_path*)paths->content;
		// ft_printf(YELLOW"Current path is %la, length: %d\n"RESET, cur_path->path_arr, cur_path->len);
		while (prev_paths && prev_paths != paths)
		{
			// ft_printf(GREEN"Decider: %d, cur_path len: %d - prev len : %d is %d, TOTAL NEW DECIDER = ", decider, cur_path->len, ((t_path*)prev_paths->content)->len, cur_path->len - ((t_path*)prev_paths->content)->len);
			decider += cur_path->len - ((t_path*)prev_paths->content)->len;
			// ft_printf("%d\n"RESET, decider);
			prev_paths = prev_paths->next;
		}
		// ft_printf(BLUE"STARTING ANTS: %d > DECIDER: %d ?\n"RESET, starting_ants, decider);
		if (starting_ants > decider)
		{
			((t_ant*)ants->content)->path = cur_path;
			starting_ants--;
			paths = paths->next;
			ants = ants->next;
		}
		else
		{
			paths = lem->paths_list;
			decider = 0;
		}
	}
}