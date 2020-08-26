/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/26 14:04:12 by osalmine         ###   ########.fr       */
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

	room_nb = room_count(lem) + 1;
	// ft_printf(RED"room_nb: %d\n", room_nb);
	if (!(que = (char**)malloc(sizeof(char*) * room_nb)))
		ft_exit(RED"Malloc error"RESET);
	que[room_nb] = NULL;
	i = 0;
	while (i < room_nb)
		que[i++] = NULL;
	i = 0;
	// while (i < room_nb)
	// {
	// 	ft_printf("que[%d] pointer: %p\n", i, que[i]);
	// 	i++;
	// }
	// ft_printf("%s", RESET);
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
	// ft_printf("ARR REVERSE arr: %la\n", arr);
	while (arr[count])
		count++;
	if (!(new_arr = (char**)malloc(sizeof(char*) * (count + 1))))
		ft_exit(RED"Malloc error"RESET);
	new_arr[count] = NULL;
	while (count)
		new_arr[start++] = ft_strdup(arr[(count--) - 1]);
	free_strsplit(&arr);
	return (new_arr);
}

static int	arr_size(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

static int  find_in_path(t_lem *lem, t_room *room)
{
    
}

static char	**solve(t_room *start, t_lem *lem)
{
	char	**prev;
	char	**que;
	t_room	*node;
	t_room	*neighbor;
	t_link	*path;
	t_list	*tmp;
	int		i;

	i = 0;
	que = create_que(lem);
	prev = create_que(lem);
	start->visited = TRUE;
	push_to_arr(que, start->name);
	while (que[i] != NULL)
	{
		if (!(node = find_room(que[i], lem)))
			ft_exit(RED"ERROR: room not found (solve)"RESET);
		tmp = node->links;
		while (tmp)
		{
			path = (t_link*)tmp->content;
			if (!(neighbor = find_room(path->room2, lem)))
				ft_exit(RED"ERROR: neighbor room not found (solve)"RESET);
			// ft_printf(MAGENTA"SOLVE\t\t:\tinspecting neighbor: %s, visited: %s, found from que: %s, ", neighbor->name, (neighbor->visited ? "TRUE" : "FALSE"), (find_from_que(que, neighbor->name) ? "TRUE" : "FALSE"));
			// if (arr_size(que) == 1)
			// 	ft_printf("array size is 1, neighbor->has_ant: %s\n"RESET, que[1], (neighbor->has_ant ? "TRUE" : "FALSE"));
			// else
			// 	ft_printf("array size is not 1\n"RESET);
			// (arr_size(que) == 1 ? !ft_strequ(que[1], neighbor->name) : (!neighbor->has_ant || neighbor->type == END))
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && !(arr_size(que) == 1 && neighbor->has_ant))
			{
				push_to_arr(que, neighbor->name);
				// ft_printf(YELLOW"SOLVE\t\t:\tpushed %s to que: %la\n"RESET, neighbor->name, que);
				neighbor->visited = TRUE;
				prev[neighbor->id] = ft_strdup(node->name);
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_strsplit(&que);
	// ft_printf(BG_WHITE BLACK"RETURN SOLVE"RESET);
	// ft_putchar('\n');
	return (prev);
}

static char **reconstruct_link(t_room *start, t_room* end, char **prev, t_lem *lem)
{
	char	**path;
	t_room	*current;

	path = create_que(lem);
	current = end;
	while (current != NULL)
	{
		// ft_printf(CYAN"RECONSTRUCT PATH\t:\tcurrent->name: %s\n"RESET, current->name);
		push_to_arr(path, current->name);
		current = find_room(prev[current->id], lem);
	}
	// ft_printf("path[0]: %s, start->name: %s\n", path[0], start->name);
	path = arr_reverse(path);
	// ft_printf("path[0]: %s, start->name: %s\n", path[0], start->name);
	if (ft_strequ(path[0], start->name))
		return (path);
	return (NULL);
}

static char	**bfs(t_room *start, t_room *end, t_lem *lem)
{
	char 	**prev;
	char 	**path;
	t_list	*tmp;

	tmp = lem->ants;
	// while (tmp)
	// {
	// 	t_ant *ant = (t_ant*)tmp->content;
	// 	ft_printf("Ant id: %d\n", ant->id);
	// 	tmp = tmp->next;
	// }
	prev = solve(start, lem);
	path = reconstruct_link(start, end, prev, lem);
	free_strsplit(&prev);
	return (path);
}

static void add_path(t_lem *lem, t_room *start, t_room *end)
{
    int i;
}

void        find_paths(t_lem *lem, t_room *start, t_room *end)
{
    
}