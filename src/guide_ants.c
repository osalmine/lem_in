/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/07/08 21:47:23 by osalmine         ###   ########.fr       */
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

static void	push_to_que(char **que, char *room)
{
	int i;

	i = 0;
	while (que[i])
		i++;
	que[i] = ft_strdup(room);
}

static char	**solve(t_room *start, t_lem *lem)
{
	char	**prev;
	char	**que;
	t_room	*node;
	t_room	*neighbor;
	t_path	*path;
	int		i;

	i = 0;
	que = create_que(lem);
	prev = create_que(lem);
	start->visited = TRUE;
	push_to_que(que, start->name);
	while (que[i] != NULL)
	{
		node = find_room(que[i], lem);
		while (node->paths)
		{
			path = (t_path*)node->paths->content;
			neighbor = find_room(path->room2, lem);
			if (!neighbor->visited && !find_from_que(que, neighbor->name))
			{
				push_to_que(que, neighbor->name);
				neighbor->visited = TRUE;
				prev[neighbor->id] = ft_strdup(node->name);
			}
			node->paths = node->paths->next;
		}
		i++;
	}
	free_strsplit(&que);
	return (prev);
}

static char **arr_reverse(char **arr)
{
	char	**tmp;
	int		count;
	int		start;

	count = 0;
	start = 0;
	while (arr[count])
		count++;
	ft_printf("Count: %d\n", count);
	if (!(tmp = (char**)malloc(sizeof(char*) * count)))
		ft_exit("Malloc error");
	tmp[count] = NULL;
	while (count)
	{
		tmp[start] = ft_strdup(arr[count - 1]);
		start++;
		count--;
	}
	free_strsplit(&arr);
	return (tmp);
}

static char **reconstruct_path(t_room *start, t_room* end, char **prev, t_lem *lem)
{
	char	**path;
	t_room	*current;

	path = create_que(lem);
	current = end;
	while (current != NULL)
	{
		push_to_que(path, current->name);
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

void    guide_ants(t_lem *lem)
{
	t_room  *start;
	t_room	*end;
	char	**path;

	start = find_room_by_type(START, lem);
	end = find_room_by_type(END, lem);
	path = bfs(start, end, lem);
	if (path != NULL)
		ft_printf(BLUE"SHORTEST PATH: %la\n"RESET, path);
	else
		ft_printf("NULL return from bfs\n");
}