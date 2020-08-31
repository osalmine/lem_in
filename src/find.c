/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:39:15 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/31 15:23:54 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_room  *find_room(char *name, t_lem *lem)
{
    t_room *found_room;
    t_room *current_room;
    t_list *tmp;

    tmp = lem->room_list;
    // ft_printf("Searching for room %s\n", name);
    // ft_printf("Find room before while\n");
    while (tmp && name)
    {
        current_room = (t_room*)tmp->content;
        if (ft_strequ(current_room->name, name))
        {
            found_room = current_room;
            // ft_printf("Find room return ok\n");
            return (found_room);
        }
        tmp = tmp->next;
    }
    // ft_printf("Find room return NULL\n");
    return (NULL);
}

t_room  *find_room_by_type(int type, t_lem *lem)
{
    t_room *found_room;
    t_room *current_room;
    t_list *head;

    head = lem->room_list;
    // ft_printf("Searching for room type: %d\n", type);
    // ft_printf("Find room by type before while\n");
    while (lem->room_list)
    {
        current_room = (t_room*)lem->room_list->content;
        if (current_room->type == type)
        {
            found_room = current_room;
            lem->room_list = head;
            // ft_printf("Find room by type return ok\n");
            return (found_room);
        }
        lem->room_list = lem->room_list->next;
    }
    lem->room_list = head;
    // ft_printf("Find room by type return NULL\n");
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