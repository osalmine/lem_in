/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:42:41 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/30 16:29:17 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int	read_command(t_lem *lem, char *line)
{
	t_list *rooms;

	if (ft_strequ(line, "##start"))
	{
		rooms = lem->room_list;
		while (rooms)
		{
			if (((t_room*)rooms->content)->type == START)
				ft_exit(RED"ERROR: multiple start rooms"RESET);
			rooms = rooms->next;
		}
		return (START);
	}
	else if (ft_strequ(line, "##end"))
	{
		rooms = lem->room_list;
		while (rooms)
		{
			if (((t_room*)rooms->content)->type == END)
				ft_exit(RED"ERROR: multiple end rooms"RESET);
			rooms = rooms->next;
		}
		return (END);
	}
	return (NORMAL);
}
