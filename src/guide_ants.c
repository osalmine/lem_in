/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/01 14:31:36 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int  room_count(t_lem* lem)
{
	int		counter;
	t_list	*tmp;

	counter = 0;
	tmp = lem->room_list;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

static char **create_que(t_lem *lem)
{
	char	**que;
	int		room_nb;
	int		i;

	room_nb = room_count(lem);
	if (!(que = (char**)malloc(sizeof(char*) * room_nb)))
		ft_exit("Malloc error");
	que[room_nb] = NULL;
	i = 0;
	while (que[i])
		que[i++] = NULL;
	return (que);
}

void    guide_ants(t_lem *lem)
{
	t_room  *start;
	char	**que;

	start = find_room_by_type(START, lem);
	start->visited = TRUE;
	que = create_que(lem);
	
	free_strsplit(&que);
}