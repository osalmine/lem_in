/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/01 17:51:29 by osalmine         ###   ########.fr       */
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

static void	push_to_que(char ***que, char *room)
{
	int i;

	i = 0;
	while (*que[i])
		i++;
	*que[i] = room;
}

static char	**solve(t_room *start, t_lem *lem)
{
	char	**prev;
	char	**que;
	t_room	*node;
	int		i;

	i = 0;
	que = create_que(lem);
	prev = create_que(lem);
	start->visited = TRUE;
	push_to_que(&que, start->name);
	ft_printf("Que: %a\n", que);
	while (que[i] != NULL)
	{
		node = find_room(que[i], lem);
		i++;
	}
	free_strsplit(&que);
	return (prev);
}

static char	**bfs(t_room *start, t_room *end, t_lem *lem)
{
	char **prev;

	prev = solve(start, lem);
	// return (reconstruct_path(start, end, prev));
	end = NULL;
	return (prev);
}

void    guide_ants(t_lem *lem)
{
	t_room  *start;
	t_room	*end;
	char	**path;

	start = find_room_by_type(START, lem);
	end = find_room_by_type(END, lem);
	path = bfs(start, end, lem);
}