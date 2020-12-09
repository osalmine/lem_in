/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:39:15 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/07 20:26:40 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_room  *find_room(char *name, t_lem *lem)
{
    t_room *current_room;
    t_list *tmp;

    tmp = lem->room_list;
    while (tmp && name)
    {
        current_room = (t_room*)tmp->content;
        if (ft_strequ(current_room->name, name))
            return (current_room);
        tmp = tmp->next;
    }
    return (NULL);
}

t_room  *find_room_by_type(int type, t_lem *lem)
{
    t_room *current_room;
    t_list *tmp;

    tmp = lem->room_list;
    while (tmp)
    {
        current_room = (t_room*)tmp->content;
        if (current_room->type == type)
            return (current_room);
        tmp = tmp->next;
    }
    return (NULL);
}

int     find_from_que(t_room **que, t_room *room)
{
    int i;

    i = 0;
    while (que[i])
    {
        if (que[i] == room)
            return (1);
        i++;
    }
    return (0);
}

int		find_in_path(t_list *list, t_room *room, t_room *end)
{
    t_list	*paths;
	t_path	*cur_path;
	t_room	**tmp;
	int		i;

	paths = list;
	if (room == end)
		return (0);
	while (paths)
	{
		i = 0;
		cur_path = (t_path*)paths->content;
		tmp = cur_path->path_arr;
		while (tmp && tmp[i])
		{
			if (tmp[i] == room)
				return (1);
			i++;
		}
		paths = paths->next;
	}
	return (0);
}

t_path  *find_path(t_list *list, t_room *room, t_room *end)
{
    t_list	*paths;
	t_path	*cur_path;
	t_room	**tmp;
	int		i;

	paths = list;
	if (room == end)
		return (NULL);
	while (paths)
	{
		i = 0;
		cur_path = (t_path*)paths->content;
		tmp = cur_path->path_arr;
		while (tmp && tmp[i])
		{
			if (tmp[i] == room)
				return (cur_path);
			i++;
		}
		paths = paths->next;
	}
	return (NULL);
}

t_link	*find_link(t_lem *lem, char *room1, char *room2)
{
	t_link	*link;
	t_list	*link_list;

	link = NULL;
	link_list = lem->link_list;
	while (link_list)
	{
		link = (t_link*)link_list->content;
		if (ft_strequ(room1, link->room1->name) && ft_strequ(room2, link->room2->name))
			return (link);
		link_list = link_list->next;
	}
	return (link);
}