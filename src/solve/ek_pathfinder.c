/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/06 21:11:24 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static char	**ek_find_path(t_lem *lem)
{
	char	**path;
	t_room	*current;
	t_room	*next;
	t_list	*links;
	char	*push_to;
	int		i;

	// ft_printf(UNDERLINE BLUE"EK_FIND_PATH\n"RESET);
	i = 0;
	path = create_arr(lem, -1);
	current = lem->start;
	push_to_arr(path, current->name);
	current->visited = TRUE;
	// t_list *paths;
	// paths = lem->paths_bef_ek;
	// while (paths)
	// {
	// 	ft_printf("%la, len: %d, in use: %d\n", ((t_path*)(paths->content))->path_arr, ((t_path*)(paths->content))->len, ((t_path*)(paths->content))->in_use);
	// 	paths = paths->next;
	// }
	push_to = NULL;
	while (path[i] && !ft_strequ(lem->end->name, path[i]))
	{
		reset_rooms(lem);
		// ft_printf("path[%d]: %s\n", i, path[i]);
		links = current->links;
		while (links)
		{
			// ft_printf("flow: %d, room1: %s, room2: %s\n", find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2);
			if (find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow == 1)
			{
				next = find_room(((t_link*)links->content)->room2, lem);
				// ft_printf("Next name: %s, visited: %s, find_in_path: %s\n", next->name, next->visited ? "TRUE" : "FALSE", find_in_path(lem->paths_list, next, lem->end) ? "TRUE" : "FALSE");
				if (!next->visited && !find_in_path(lem->paths_list, next, lem->end))
				{
					// ft_printf("Ok\n");
					current = next;
					current->visited = TRUE;
					push_to = current->name;
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
			find_link(lem, path[i], push_to)->flow = INF;
			push_to_arr(path, push_to);
			push_to = NULL;
		}
		i++;
		// if (!path[i])
		// 	ft_printf("PATH LIST ENDS, i : %d\n", i);
	}
	// ft_printf(BLUE"PATH: %la\n"RESET, path);
	// ft_printf("path[arr_size(path) - 1]: %s, lem->end->name: %s\n", path[arr_size(path) - 1], lem->end->name);
	if (!check_for_dup_path_size_1(lem, path) && ft_strequ(path[arr_size(path) - 1], lem->end->name))
		return (path);
	i = lem->room_count;
	while (i--)
		if (path && path[i])
			ft_strdel(&path[i]);
	free (path);
	return (NULL);
}

void	flows_pathfinder(t_lem *lem)
{
	char	**path;
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
			free_strsplit(&path);
		}
	}
}