/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/21 13:49:09 by osalmine         ###   ########.fr       */
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

static void	push_to_arr(char **que, char *room)
{
	int i;

	i = 0;
	while (que[i])
		i++;
	que[i] = ft_strdup(room);
}

static char **arr_reverse(char **arr)
{
	char	**new_arr;
	int		count;
	int		start;

	count = 0;
	start = 0;
	while (arr[count])
		count++;
	if (!(new_arr = (char**)malloc(sizeof(char*) * (count + 1))))
		ft_exit("Malloc error");
	new_arr[count] = NULL;
	while (count)
		new_arr[start++] = ft_strdup(arr[(count--) - 1]);
	free_strsplit(&arr);
	return (new_arr);
}

static char	**solve(t_room *start, t_lem *lem)
{
	char	**prev;
	char	**que;
	t_room	*node;
	t_room	*neighbor;
	t_path	*path;
	t_list	*tmp;
	int		i;

	i = 0;
	que = create_que(lem);
	prev = create_que(lem);
	start->visited = TRUE;
	push_to_arr(que, start->name);
	while (que[i] != NULL)
	{
		node = find_room(que[i], lem);
		tmp = node->paths;
		while (tmp)
		{
			ft_printf("Node: %s\n", node->name);
			path = (t_path*)tmp->content;
			neighbor = find_room(path->room2, lem);
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && !neighbor->has_ant)
			{
				push_to_arr(que, neighbor->name);
				neighbor->visited = TRUE;
				prev[neighbor->id] = ft_strdup(node->name);
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_strsplit(&que);
	return (prev);
}

static char **reconstruct_path(t_room *start, t_room* end, char **prev, t_lem *lem)
{
	char	**path;
	t_room	*current;

	path = create_que(lem);
	current = end;
	while (current != NULL)
	{
		push_to_arr(path, current->name);
		current = find_room(prev[current->id], lem);
	}
	path = arr_reverse(path);
	if (ft_strequ(path[0], start->name))
		return (path);
	return (NULL);
}

static char	**bfs(t_room *start, t_room *end, t_lem *lem)
{
	char **prev;

	prev = solve(start, lem);
	return (reconstruct_path(start, end, prev, lem));
}

static void	reset_rooms(t_lem *lem)
{
	t_list	*tmp;
	t_room	*room;

	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->visited = FALSE;
		tmp = tmp->next;
	}
}

void		guide_ants(t_lem *lem)
{
	t_room  *start;
	t_room	*end;
	char	**path;

	start = find_room_by_type(START, lem);
	end = find_room_by_type(END, lem);
	while (end->has_ant != lem->ant_nb)
	{
		path = bfs(start, end, lem);
			if (path != NULL)
		ft_printf(BLUE"SHORTEST PATH: %la\n"RESET, path);
		else
			ft_printf(RED"ERROR: No path found\n"RESET);
		reset_rooms(lem);
		free_strsplit(&path);
		end->has_ant++;
	}
}