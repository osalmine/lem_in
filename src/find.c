/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:39:15 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/20 17:23:18 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_room  *find_room(char *name, t_lem *lem)
{
    t_room *found_room;
    t_room *current_room;
    t_list *head;

    head = lem->room_list;
    while (lem->room_list->next)
    {
        current_room = (t_room*)lem->room_list->content;
        if (ft_strequ(current_room->name, name))
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