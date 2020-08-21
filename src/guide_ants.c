/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/18 20:10:31 by osalmine         ###   ########.fr       */
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
	// ft_printf("room_nb: %d\n", room_nb);
	if (!(que = (char**)malloc(sizeof(char*) * room_nb)))
		ft_exit("Malloc error");
	que[room_nb] = NULL;
	i = 0;
	while (i < room_nb)
		que[i++] = NULL;
	// i = 0;
	// while (i++ < room_nb)
	// 	ft_printf("que[%d] pointer: %p\n", i, que[i]);
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
		ft_exit("Malloc error");
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
		if (!(node = find_room(que[i], lem)))
			ft_exit("ERROR: room not found (solve)\n");
		tmp = node->paths;
		while (tmp)
		{
			path = (t_path*)tmp->content;
			if (!(neighbor = find_room(path->room2, lem)))
				ft_exit("Error: neighbor room not found (solve)\n");
			// ft_printf(MAGENTA"SOLVE\t\t:\tinspecting neighbor: %s, visited: %s, found from que: %s, ", neighbor->name, (neighbor->visited ? "TRUE" : "FALSE"), (find_from_que(que, neighbor->name) ? "TRUE" : "FALSE"));
			// if (arr_size(que) == 2)
			// 	ft_printf("array size is 2, que[1]: %s = neighbor->name: %s, %s\n"RESET, que[1], neighbor->name, (ft_strequ(que[1], neighbor->name) ? "TRUE" : "FALSE"));
			// else
			// 	ft_printf("array size is not 2 (%d), neighbor->has_ant: %s, neighbor->type: %d\n"RESET, arr_size(que), (neighbor->has_ant ? "TRUE" : "FALSE"), neighbor->type);
			// (arr_size(que) == 1 ? !ft_strequ(que[1], neighbor->name) : (!neighbor->has_ant || neighbor->type == END))
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && !(arr_size(que) == 1 && neighbor->has_ant))
			{
				push_to_arr(que, neighbor->name);
				// ft_printf(YELLOW"SOLVE\t\t:\tpushing %s to que: %la\n"RESET, neighbor->name, que);
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
	path = reconstruct_path(start, end, prev, lem);
	return (path);
}

static void	reset_rooms(t_lem *lem)
{
	t_list	*tmp;
	t_room	*room;

	tmp = lem->room_list;
	// ft_printf(BG_RED"Reset loop"RESET);
	// write(1, "\n", 1);
	while (tmp)
	{
		room = (t_room*)tmp->content;
		// ft_printf("Room name: %s\n", room->name);
		room->visited = FALSE;
		// if (room->type == NORMAL)
		// 	room->has_ant = FALSE;
		tmp = tmp->next;
	}
}

static void	reset_turn(t_lem *lem)
{
	// t_room	*prev_room;
	t_ant	*cur_ant;
	t_list	*ant_list;

	ant_list = lem->ants;
	while (ant_list)
	{
		cur_ant = (t_ant*)ant_list->content;
		if (cur_ant->has_moved)
		{
			// prev_room = find_room(cur_ant->path[cur_ant->move_nb - 1], lem);
			// prev_room->has_ant = FALSE;
			cur_ant->has_moved = FALSE;
		}
		ant_list = ant_list->next;
	}
}

static void	turn_loop(t_lem *lem, t_room *start, t_room *end)
{
	int		i;
	t_ant	*cur_ant;
	t_list	*ant_list;
	t_room	*next_room;
	
	i = 0;
	ant_list = lem->ants;
	// ft_printf(BG_RED"NEW TURN"RESET);
	// write(1, "\n", 1);
	while (i < lem->ant_nb)
	{
		cur_ant = (t_ant*)ant_list->content;
		// ft_printf(MAGENTA"TURN LOOP ant id: %d, moves: %d\n"RESET, cur_ant->id, cur_ant->move_nb);
		if (cur_ant->room->type != END)
		{
			if (!cur_ant->path)
				cur_ant->path = bfs(start, end, lem);
			if (cur_ant->path == NULL && cur_ant->id == 1)
				ft_exit(RED"ERROR: No path found\n"RESET);
			// if (cur_ant->path == NULL)
			// 	ft_printf(RED"No path found\n"RESET);
			// else
			// 	ft_printf(BLUE"SHORTEST PATH: %la\n"RESET, cur_ant->path);
			if (cur_ant->path != NULL)
			{
				next_room = find_room(cur_ant->path[cur_ant->move_nb + 1], lem);
				if (!next_room->has_ant || next_room->type == END)
				{
					cur_ant->room->has_ant = FALSE;
					cur_ant->room = next_room;
					ft_printf("L%d-%s ", cur_ant->id, cur_ant->room->name);
					if (cur_ant->room->type == NORMAL)
						cur_ant->room->has_ant = TRUE;
					cur_ant->has_moved = TRUE;
					cur_ant->move_nb++;
					if (cur_ant->room->type == END)
					{
						// ft_printf(BG_CYAN BLACK"ANT %d REACHED END"RESET, cur_ant->id);
						// write(1, "\n", 1);
						end->has_ant++;
					}
				}
			}
			reset_rooms(lem);
		}
		i++;
		ant_list = ant_list->next;
		reset_turn(lem);
	}
	ft_putchar('\n');
	lem->moves_count++;
	// free_strsplit(&path);
}

void		guide_ants(t_lem *lem)
{
	t_room  *start;
	t_room	*end;

	if (!(start = find_room_by_type(START, lem)))
		ft_exit("ERROR: No start room (guide_ants)\n");
	if (!(end = find_room_by_type(END, lem)))
		ft_exit("ERROR: No end room (guide_ants)\n");
	while (end->has_ant != lem->ant_nb)
	{
		// t_list	*tmp;

		// tmp = lem->room_list;
		// ft_printf(BG_GREEN BLACK"Room list:"RESET);
		// write(1, "\n", 1);
		// while (tmp)
		// {
		// 	ft_printf("%s\n", ((t_room*)tmp->content)->name);
		// 	tmp = tmp->next;
		// }
		t_list	*tmp_ant;

		tmp_ant = lem->ants;
		while (tmp_ant)
		{
			// ft_printf(CYAN"Ant id: %d\n"RESET, ((t_ant*)tmp_ant->content)->id);
			tmp_ant = tmp_ant->next;
		}
		turn_loop(lem, start, end);
		// ft_printf("%send node %sant amount: %d, ant amount: %d\n"RESET, RED, BLUE, end->has_ant, lem->ant_nb);
	}
}