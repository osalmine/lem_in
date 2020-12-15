/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:50:08 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/14 12:56:32 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// #include <time.h>


// static void	reset_path(t_lem *lem, t_path *path)
// {
// 	int		i;
// 	t_link	*link;
// 	t_room	*room;

// 	i = 0;
// 	// ft_printf("resetting path\n");
// 	while (path->path_arr[i + 1])
// 	{
// 		if (!(link = find_link(path->path_arr[i], path->path_arr[i + 1])))
// 			ft_exit(RED"ERROR: link not found (reset_path)"RESET);
// 		// if (ft_strequ(link->room1, node->name))
// 		// 	break ;
// 		link->flow = INF;
// 		if (!(link = find_link(path->path_arr[i + 1], path->path_arr[i])))
// 			ft_exit(RED"ERROR: link not found (reset_path)"RESET);
// 		link->flow = INF;
// 		room = find_room(path->path_arr[i]->name, lem);
// 		room->weight = INF - 1;
// 		i++;
// 	}
// 	// ft_printf("resetted path\n");
// }

// static void	remove_path(t_lem *lem, t_path *path)
// {
// 	t_list *lst;

// 	lst = lem->paths_bef_ek;
// 	// ft_printf("lst pointer: %p\n", lst);
// 	// ft_printf("path to remove: %la\n", path->path_arr);
// 	while (lst->next)
// 	{
// 		// ft_printf("REMOVE PATH LOOP\n");
// 		// ft_printf("next->content before swap: %la\n", ((t_path*)lst->next->content)->path_arr);
// 		if (((t_path*)lst->next->content) == path)
// 		{
// 			// ft_printf(BG_RED BLACK"REMOVE PATH MATCHING PATH FOUND"RESET);
// 			// ft_printf("cur path arr: %la, path arr: %la\n", ((t_path*)lst->next->content)->path_arr, path->path_arr);
// 			// ft_printf("\n");
// 			lst->next = lst->next->next;
// 			free_a_path(&path, 0);
// 			break ;
// 		}
// 		lst = lst->next;
// 	}
// 	// ft_printf("next->content before swap: %la, p: %p\n", ((t_path*)lst->next) ? ((t_path*)lst->next->content)->path_arr : NULL, ((t_path*)lst->next) ? ((t_path*)lst->next->content)->path_arr : NULL);
// 	// free_a_path(&path, 0);
// 	// ft_printf("path arr addr: %p\n", path->path_arr);
// 	// path = NULL;
// 	// ft_printf("path address: %p\n", path);
// }

static int	check_for_flow_weight(t_room *current, t_room *next)
{
	int		check;
	t_link	*link;
	// t_path	*path;

	check = 0;
	if (!(link = find_link(current, next)))
		ft_exit(RED"ERROR: can't find link (check_for_flow)"RESET);
	// if ((path = find_path(lem->paths_bef_ek, next, lem->end)))
	// {
	// 	if (path->in_use == FALSE)
	// 	{
	// 		check = 1;
	// 		// ft_printf(MAGENTA"PATH IS NOT IN USE: CHECK 1\n"RESET);
	// 	}
	// }
	// if (link->flow == INF || link->flow == -1)
	if ((link->flow == INF || link->flow == -1) && ((next->weight == INF - 1 && next->type != END) || current->weight + 1 < next->weight))
	{
		check = 1;
		// ft_printf(MAGENTA"FLOW ASSIGNS CHECK TO 1\n"RESET);
		// if (link->flow == INF)
		// 	ft_printf("link flow is INF\n");
		// if (link->flow == -1)
		// 	ft_printf("link flow is -1\n");
	}
	if (next->type != END && ((next->weight == INF - 1 && next->type != END) || current->weight + 1 < next->weight))
	{
		check = 1;
		// ft_printf(YELLOW"WEIGHT ASSIGNS CHECK TO 1\n"RESET);
	}
	if (next->type == END && link->flow != 1)
		check = 1;
	// ft_printf(GREEN"room1: %s, room2: %s, flow: %d, cur weight + 1: %d, next weight: %d, check: %d\n"RESET, link->room1->name, link->room2->name, link->flow, current->weight + 1, next->weight, check);
	return (check);
}

static void	solve_loop(t_lem *lem, t_room ***prev, t_room ***que, int i)
{
	int		can_use_link;
	t_room	*node;
	t_room	*neighbor;
	t_list	*tmp;
	// t_path	*path;

	node = (*que)[i];
	tmp = node->links;
	while (tmp)
	{
		neighbor = ((t_link*)tmp->content)->room2;
		// ft_printf(MAGENTA"SOLVE\t\t:\tinspecting neighbor: %s (%p), visited: %s, found from que: %s, ", neighbor->name, neighbor, (neighbor->visited ? "TRUE" : "FALSE"), (find_from_que((*que), neighbor) ? "TRUE" : "FALSE"));
		// ft_printf("found from path: %s\n"RESET, (find_in_path(lem->paths_bef_ek, neighbor, lem->end) ? "TRUE" : "FALSE"));
		can_use_link = check_for_flow_weight(node, neighbor);
		if (!neighbor->visited && !find_from_que(*que, neighbor) \
			&& ((can_use_link || !find_in_path(lem->paths_bef_ek, neighbor, lem->end)) \
			&& (!can_use_link ? neighbor->type != END : TRUE)))
		{
			push_to_room_arr(*que, neighbor);
			// ft_printf(YELLOW"SOLVE\t\t:\tpushed %s to que: ", neighbor->name);
			// for (int i = 0; (*que)[i]; i++)
			// 	ft_printf("%s, ", (*que)[i] ? (*que)[i]->name : NULL);
			// ft_printf("\n"RESET);
			neighbor->visited = TRUE;
			(*prev)[neighbor->id] = node;
			// if (node->type != END && neighbor->type != END && node->weight + 1 < neighbor->weight && (path = find_path(lem->paths_bef_ek, neighbor, lem->end)))
			// if (node->type != END && neighbor->type != END && node->weight + 1 < neighbor->weight && find_in_path(lem->paths_bef_ek, neighbor, lem->end))
			// {
			// 	path = find_path(lem->paths_bef_ek, neighbor, lem->end);
			// 	// ft_printf(RED"PATH\t:\t: IN_USE: %d\n"RESET, path->in_use);
			// 	// ft_printf("current->name: %s, next->name: %s\n", node->name, neighbor->name);
			// 	// ft_printf(REVERSED"PATH RETURNED FROM FIND_PATH: %la\n"RESET, path->path_arr);
			// 	if (path && path->in_use == TRUE)
			// 	{
			// 		reset_path(lem, path);
			// 		// remove_path(lem, path);
			// 		path->in_use = FALSE;
			// 		// ft_printf(RED"Removed a path\n"RESET);
			// 	}
			// }
			// ft_printf(BLUE"Assigned %s to prev at id: %d : %s\n"RESET, node->name, neighbor->id, (*prev)[neighbor->id]->name);
			// ft_printf(BG_CYAN BLACK"FULL PREV ARRAY IN SOLVE:"RESET);
			// ft_putchar('\n');
			// int j = 0;
			// while (j < lem->room_count)
			// {
			// 	ft_printf(CYAN"%s, "RESET, (*prev)[j] ? (*prev)[j]->name : NULL);
			// 	j++;
			// }
			// ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

static t_room	**solve(t_lem *lem)
{
	t_room	**prev;
	t_room	**que;
	int		i;

	i = 0;
	que = create_room_arr(lem, -1);
	prev = create_room_arr(lem, -1);
	lem->start->visited = TRUE;
	push_to_room_arr(que, lem->start);
	while (que[i] != NULL)
	{
		solve_loop(lem, &prev, &que, i);
		i++;
	}
	// ft_printf("SOLVE LOOP TERATIONS: %d\n", i);
	// ft_memdel((void**)que);
	// ft_printf(BG_WHITE BLACK"RETURN SOLVE"RESET);
	// ft_putchar('\n');
	// ft_printf(BG_CYAN BLACK"FINAL FULL PREV ARRAY IN SOLVE BEF RETURN:"RESET);
	// ft_putchar('\n');
	// int j = 0;
	// while (j < lem->room_count)
	// {
	// 	ft_printf(CYAN"%s, "RESET, prev[j] ? prev[j]->name : NULL);
	// 	j++;
	// }
	// ft_putchar('\n');
	// while (1) ;
	free(que);
	return (prev);
}

static t_room	**reconstruct_path(t_room ***prev, t_lem *lem)
{
	t_room	**path;
	t_room	*current;

	path = create_room_arr(lem, -1);
	current = lem->end;
	// ft_printf(BG_CYAN BLACK"FULL PREV ARRAY IN RECONSTRUCT_PATH:"RESET);
	// ft_putchar('\n');
	// int j = 0;
	// while (j < lem->room_count)
	// {
	// 	ft_printf(CYAN"prev[%d]: ptr: %p, name: %s\n"RESET, j, (*prev)[j], (*prev)[j] ? (*prev)[j]->name : NULL);
	// 	j++;
	// }
	// ft_printf("1. End room id: %d, current id: %d\n", lem->end->id, current->id);
	// ft_putchar('\n');
	// int i = 0;
	while (current != NULL)
	{
		// i++;
		// ft_printf("2. End room id: %d, current id: %d\n", lem->end->id, current->id);
		// ft_printf(CYAN"RECONSTRUCT PATH\t:\tcurrent->name: %s, %p\n"RESET, current->name, current);
		push_to_room_arr(path, current);
		// ft_printf("3. End room id: %d, current id: %d\n", lem->end->id, current->id);
		// ft_printf("RECONSTRUCT PATH\t:\tprev[current->id: %d]: %s, %p\n", current->id, (*prev)[current->id] && (*prev)[current->id]->name ? (*prev)[current->id]->name : NULL, (*prev)[current->id]);
		// if (prev[current->id])
		// 	current = find_room(prev[current->id]->name, lem);
		// else
		// 	current = NULL;
		// 	current = lem->room_table[current->id][(*prev)[current->id]->id];
		// ft_printf(YELLOW"RECONSTRUCT PATH\t:\tprev[current->id: %d]: %s, prev[current->id]->id: %d\n", current->id, (*prev)[current->id] ? (*prev)[current->id]->name : NULL, (*prev)[current->id] ? (*prev)[current->id]->id : -1);
		// ft_printf("lem->room_links_arr[current->id][(*prev)[current->id]->id]: %d, lem->room_arr[lem->room_links_arr[current->id][(*prev)[current->id]->id]]->name: %s\n"RESET, (*prev)[current->id] ? lem->room_links_arr[current->id][(*prev)[current->id]->id] : -1, (*prev)[current->id] && lem->room_links_arr[current->id][(*prev)[current->id]->id] != -1 ? lem->room_arr[lem->room_links_arr[current->id][(*prev)[current->id]->id]]->name : NULL);
		if ((*prev)[current->id] && lem->room_links_arr[current->id][(*prev)[current->id]->id] != -1)
			current = lem->room_arr[lem->room_links_arr[current->id][(*prev)[current->id]->id]];
		else
			current = NULL;
		// if (current)
		// 	ft_printf(BLUE"RECONSTRUCT PATH\t:\tnext current->name: %s, %p\n"RESET, current->name, current);
		// else
		// 	ft_printf(BLUE"CURRENT IS NULL\n"RESET);
	}
	// ft_printf("RECONSTRUCT PATH ROUNDS: %d\n", i);
	path = room_arr_reverse(path);
	// ft_printf("PATH: %la\n", path);
	// ft_printf("path[0]->name: %s, lem->start->name: %s\n", path[0]->name, lem->start->name);
	if (ft_strequ(path[0]->name, lem->start->name))
		return (path);
	// i = lem->room_count;
	free (path);
	return (NULL);
}

t_room		**bfs(t_lem *lem)
{
	t_room 	**prev;
	t_room 	**path;
	int		i;

	// clock_t start_1 = clock();

	prev = solve(lem);

	// while (1) ;

	// clock_t end_1 = clock();
	// double elapsed_1 = (double)(end_1 - start_1)/CLOCKS_PER_SEC;

	// ft_printf(YELLOW"Time measeured for solve in bfs: %.3f seconds.\n"RESET, elapsed_1);
	
	// clock_t start_2 = clock();

	// ft_printf(BG_CYAN BLACK"FULL PREV ARRAY IN BFS AFTER SOLVE:"RESET);
	// ft_putchar('\n');
	// int j = 0;
	// while (j < lem->room_count)
	// {
	// 	ft_printf(CYAN"prev[%d]: ptr: %p, name: %s\n"RESET, j, prev[j], prev[j] ? prev[j]->name : NULL);
	// 	j++;
	// }

	path = reconstruct_path(&prev, lem);

	// clock_t end_2 = clock();
	// double elapsed_2 = (double)(end_2 - start_2)/CLOCKS_PER_SEC;

	// ft_printf(GREEN"Time measeured for reconstruct path in bfs: %.3f seconds.\n"RESET, elapsed_2);

	// free_strsplit(&prev);

	i = lem->room_count;
	free (prev);

	// t_list *pths;
	// pths = lem->paths_bef_ek;
	// while (pths)
	// {
	// 	ft_printf("PATH ARR: %la\n", ((t_path*)pths->content)->path_arr);
	// 	pths = pths->next;
	// }
	return (path);
}