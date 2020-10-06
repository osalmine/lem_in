/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:17:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/25 18:21:44 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static char	**ek_find_path(t_lem *lem)
{
	char	**path;
	t_room	*current;
	t_room	*next;
	t_list	*links;
	int		i;

	i = 0;
	reset_rooms(lem);
	path = create_arr(lem, -1);
	current = find_room_by_type(START, lem);
	push_to_arr(path, current->name);
	current->visited = TRUE;
	// t_list *paths;
	// paths = lem->paths_list;
	// while (paths)
	// {
	// 	ft_printf("%la, len: %d\n", ((t_path*)(paths->content))->path_arr, ((t_path*)(paths->content))->len);
	// 	paths = paths->next;
	// }
	while (path[i])
	{
		// ft_printf("path[%d]: %s\n", i, path[i]);
		links = current->links;
		while (links)
		{
			// ft_printf("flow: %d, room1: %s, room2: %s\n", find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2);
			if (find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow == 1)
			{
				next = find_room(((t_link*)links->content)->room2, lem);
				// ft_printf("Next name: %s\n", next->name);
				if (!next->visited && !find_in_path(lem->paths_list, next, find_room_by_type(END, lem)))
				{
					// ft_printf("Ok\n");
					current = next;
					current->visited = TRUE;
					push_to_arr(path, current->name);
					break ;
				}
			}
			links = links->next;
		}
		i++;
	}
	// ft_printf(BLUE"PATH: %la\n"RESET, path);
	if (!check_for_dup_path(lem, path) && ft_strequ(path[arr_size(path) - 1], (find_room_by_type(END, lem))->name))
		return (path);
	return (NULL);
}

void	flows_pathfinder(t_lem *lem)
{
	char **path;

    // t_list *lst;
    // lst = lem->room_list;
    // while (lst)
    // {
    //     ft_printf("WEIGHT FOR ROOM %s: %d\n", ((t_room*)lst->content)->name, ((t_room*)lst->content)->weight);
    //     lst = lst->next;
    // }
	while ((path = ek_find_path(lem)))
	{
		add_path(lem, path);
		free_strsplit(&path);
	}
}