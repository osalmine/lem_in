/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:11:08 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/03 01:42:10 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int		check_for_dup_path_size_1(t_lem *lem, t_room **path)
{
	t_list	*paths;
	int		i;
	int		path_len;

	paths = lem->paths_list;
	path_len = room_arr_size(path) - 1;
	while (paths && path_len == 1)
	{
		i = 0;
		if (((t_path*)paths->content)->len == path_len)
		{
			while (path[i] && ((t_path*)paths->content)->path_arr[i] == path[i])
				i++;
			if (i == path_len + 1)
				return (1);
		}
		paths = paths->next;
	}
	return (0);
}

int		check_for_dup_path(t_list *paths_lst, t_room **path)
{
	t_list	*paths;
	int		i;
	int		path_len;

	paths = paths_lst;
	path_len = room_arr_size(path) - 1;
	while (paths)
	{
		i = 0;
		if (((t_path*)paths->content)->len == path_len)
		{
			while (path[i] && ((t_path*)paths->content)->path_arr[i] == path[i])
				i++;
			if (i == path_len + 1)
				return (1);
		}
		paths = paths->next;
	}
	return (0);
}

int		min_3(int x, int y, int z)
{
	if (x < y)
		return (x < z ? x : z);
	else
		return (y < z ? y : z);
}

int		max_flow(t_lem *lem)
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
