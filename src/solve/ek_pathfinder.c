/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/11/02 14:23:06 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static t_room	**ek_find_path(t_lem *lem)
{
	t_room	**path;
	t_room	*current;
	t_room	*next;
	t_list	*links;
	t_room	*push_to;
	int		i;

	// ft_printf(UNDERLINE BLUE"EK_FIND_PATH\n"RESET);
	i = 0;
	path = create_room_arr(lem, -1);
	current = lem->start;
	push_to_room_arr(path, current);
	current->visited = TRUE;
	// t_list *paths;
	// paths = lem->paths_bef_ek;
	// while (paths)
	// {
	// 	ft_printf("%la, len: %d, in use: %d\n", ((t_path*)(paths->content))->path_arr, ((t_path*)(paths->content))->len, ((t_path*)(paths->content))->in_use);
	// 	paths = paths->next;
	// }
	push_to = NULL;
	while (path[i] && lem->end != path[i])
	{
		reset_rooms(lem);
		// ft_printf("path[%d]: %s\n", i, path[i]);
		links = current->links;
		while (links)
		{
			// ft_printf("flow: %d, room1: %s, room2: %s\n", find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2);
			// ft_printf("room1: %s, room2: %s Flow: %d, ptr: %p\n", ((t_link*)links->content)->room1->name, ((t_link*)links->content)->room2->name, ((t_link*)links->content)->flow, ((t_link*)links->content));
			if (((t_link*)links->content)->flow == 1)
			{
				next = ((t_link*)links->content)->room2;
				// ft_printf("Next name: %s, visited: %s, find_in_path: %s\n", next->name, next->visited ? "TRUE" : "FALSE", find_in_path(lem->paths_list, next, lem->end) ? "TRUE" : "FALSE");
				if (!next->visited && !find_in_path(lem->paths_list, next, lem->end))
				{
					// ft_printf("Ok\n");
					current = next;
					current->visited = TRUE;
					push_to = current;
					if (next->type == END)
						break ;
				}
			}
			links = links->next;
		}
		if (push_to)
		{
			// ft_printf(YELLOW"PUSHING: %s TO ARR\n"RESET, push_to);
			// ft_printf(CYAN"Finind link between %s and %s\n"RESET, path[i], push_to);
			find_link(lem, path[i]->name, push_to->name)->flow = INF;
			push_to_room_arr(path, push_to);
			push_to = NULL;
		}
		i++;
		// if (!path[i])
		// 	ft_printf("PATH LIST ENDS, i : %d\n", i);
	}
	// ft_printf(BLUE"PATH: %la\n"RESET, path);
	// ft_printf("path[arr_size(path) - 1]: %s, lem->end->name: %s\n", path[arr_size(path) - 1], lem->end->name);
	if (!check_for_dup_path_size_1(lem, path) && path[room_arr_size(path) - 1] == lem->end)
		return (path);
	return (NULL);
}

void	flows_pathfinder(t_lem *lem)
{
	t_room	**path;
	int		i;

	// ft_printf(REVERSED"FLOWS_PATHFINDER"RESET);
	// ft_printf("\n");
    // t_list *lst;
    // lst = lem->room_list;
    // while (lst)
    // {
    //     ft_printf("WEIGHT FOR ROOM %s: %d\n", ((t_room*)lst->content)->name, ((t_room*)lst->content)->weight);
    //     lst = lst->next;
    // }
	i = 0;
	lem->max_flow = max_flow(lem);
	while ((path = ek_find_path(lem)) || i++ < lem->max_flow)
	{
		// ft_printf(BOLD RED"NEW EK LOOP, i: %d\n"RESET, i);
		if (path)
		{
			add_path(lem, path, &(lem->paths_list));
			free(path);
		}
	}
}