/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:39:15 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/21 10:46:39 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_room  *find_room(char *name, t_lem *lem)
{
    t_room *found_room;
    t_room *current_room;
    t_list *tmp;

    tmp = lem->room_list;
    while (tmp && name)
    {
        current_room = (t_room*)tmp->content;
        if (ft_strequ(current_room->name, name))
        {
            found_room = current_room;
            return (found_room);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

t_room  *find_room_by_type(int type, t_lem *lem)
{
    t_room *found_room;
    t_room *current_room;
    t_list *head;

    head = lem->room_list;
    while (lem->room_list)
    {
        current_room = (t_room*)lem->room_list->content;
        if (current_room->type == type)
        {
            found_room = current_room;
            lem->room_list = head;
            return (found_room);
        }
        lem->room_list = lem->room_list->next;
    }
    lem->room_list = head;
    return (NULL);
}

int     find_from_que(char **que, char *name)
{
    int i;

    i = 0;
    while (que[i])
    {
        if (ft_strequ(que[i], name))
            return (1);
        i++;
    }
    return (0);
}