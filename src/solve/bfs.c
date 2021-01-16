/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:50:08 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/14 15:41:53 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int		check_for_flow_weight(t_lem *lem, t_room *current, t_room *next, int nb, t_room ***prev)
{
	int		check;
	int		limit;
	t_link	*link;
	t_room	*parent;

	nb = 0;

	check = 0;
	limit = 1;
	parent = NULL;
	if (!(link = find_link(current, next)))
		ft_exit(RED"ERROR: can't find link (check_for_flow)"RESET);
	if ((*prev)[current->id])
			parent = lem->room_arr[(*prev)[current->id]->id];
		// if (parent)
		// 	ft_printf("CURRENT: %s PARENT: %s, in_path: %s\n", current->name, parent->name, parent->in_path ? "TRUE" : "FALSE");
		// else
		// 	ft_printf("CURRENT: %s, PARENT: %p\n", current->name, parent);
	if (parent && current->in_path == TRUE && parent->in_path == FALSE)
		limit = INF;
	// if (nb == 1 && ((link->flow == INF || link->flow == -1) && ((next->weight == INF - 1 \
	// 	&& next->type != END) || current->weight + 1 < next->weight)))
	if (link->flow != 1 && link->flow != limit)
	{
		check = 1;
		// ft_printf(MAGENTA"FLOW ASSIGNS CHECK TO 1\n"RESET);
		// if (link->flow == INF)
		// 	ft_printf("link flow is INF\n");
		// if (link->flow == -1)
		// 	ft_printf("link flow is -1\n");
	}
	// if (nb == 2)
	// {
	// 	//  if (&& current->in_path == TRUE && find_hashed_room(lem, ))
	// 	// find_from_que()
	// 	// ft_printf("current->id: %d, prev[current->id]: %p\n", current->id, (*prev)[current->id]);
	// 	if ((*prev)[current->id])
	// 		parent = lem->room_arr[(*prev)[current->id]->id];
	// 	// if (parent)
	// 	// 	ft_printf("CURRENT: %s PARENT: %s, in_path: %s\n", current->name, parent->name, parent->in_path ? "TRUE" : "FALSE");
	// 	// else
	// 	// 	ft_printf("CURRENT: %s, PARENT: %p\n", current->name, parent);
	// 	if (parent && current->in_path == TRUE && parent->in_path == FALSE)
	// 		limit = INF;
	// }
	// if (limit == 0)
	// 	ft_printf(BOLD RED"LIMIT 0\n"RESET);
	// if (nb == 2 && link->flow != 1 && link->flow != limit)
	// 	check = 1;
	// if (nb == 2 && (next->type != END && (next->weight == INF - 1 \
	// 	|| current->weight + 1 < next->weight)))
	// {
	// 	check = 1;
	// 	// ft_printf(YELLOW"WEIGHT ASSIGNS CHECK TO 1\n"RESET);
	// }
	if (next->type == END && link->flow != 1)
		check = 1;
	// if (nb == 2)
		// ft_printf(GREEN"room1: %s, room2: %s, flow: %d, cur weight + 1: %d, next weight: %d, check: %d\n"RESET, link->room1->name, link->room2->name, link->flow, current->weight + 1, next->weight, check);
	return (check);
}

static void		solve_loop(t_lem *lem, t_room ***prev, t_room ***que, int i, int nb)
{
	int		can_use_link;
	t_room	*node;
	t_room	*neighbor;
	t_list	*tmp;

	node = (*que)[i];
	tmp = node->links;
	while (tmp)
	{
		neighbor = ((t_link*)tmp->content)->room2;
		// if (nb == 2)
			// ft_printf(MAGENTA"SOLVE\t\t:\tNode: %s, visited: %s, can_use_link: %s\n"RESET, neighbor->name, neighbor->visited ? "TRUE" : "FALSE", can_use_link ? "TRUE" : "FALSE");
		can_use_link = check_for_flow_weight(lem, node, neighbor, nb, prev);
		if (!neighbor->visited && can_use_link)
		{
			push_to_room_arr(*que, neighbor);
			// if (nb == 2)
			// {
				// ft_printf(YELLOW"SOLVE\t\t:\tpushed %s to que from parent %s: ", neighbor->name, node->name);
				// for (int i = 0; (*que)[i]; i++)
				// 	ft_printf("%s, ", (*que)[i] ? (*que)[i]->name : NULL);
				// ft_printf("\n"RESET);
			// }
			neighbor->visited = TRUE;
			(*prev)[neighbor->id] = node;
		}
		tmp = tmp->next;
	}
}

static t_room	**solve(t_lem *lem, int nb)
{
	t_room	**prev;
	t_room	**que;
	int		i;

	i = 0;
	que = create_room_arr(lem);
	prev = create_room_arr(lem);
	lem->start->visited = TRUE;
	lem->start->in_path = TRUE;
	push_to_room_arr(que, lem->start);
	// ft_printf(RED"START\n"RESET);
	// ft_printf("NB: %d\n", nb);
	while (que[i] != NULL)
	{
		// if (nb == 2)
			// ft_printf(CYAN"Parent node: %s\n"RESET, que[i]->name);
		solve_loop(lem, &prev, &que, i, nb);
		i++;
	}
	// ft_printf("SOLVE LOOP ITERATIONS: %d\n", i);
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
	free(que);
	return (prev);
}

static t_room	**reconstruct_path(t_room ***prev, t_lem *lem)
{
	t_room	**path;
	t_room	*current;

	path = create_room_arr(lem);
	current = lem->end;
	// if (nb == 2)
	// {
		// ft_printf(BG_CYAN BLACK"FULL PREV ARRAY IN RECONSTRUCT_PATH:"RESET);
		// ft_putchar('\n');
		// int j = 0;
		// while (j < lem->room_count)
		// {
		// 	ft_printf(CYAN"prev[%d]: ptr: %p, name: %s\n"RESET, j, (*prev)[j], (*prev)[j] ? (*prev)[j]->name : NULL);
		// 	j++;
		// }
		// ft_printf("\n");
	// }
	while (current != NULL)
	{
		// ft_printf(CYAN"RECONSTRUCT PATH\t:\tcurrent->name: %s, %p\n"RESET, current->name, current);
		push_to_room_arr(path, current);
		// if (nb == 2)
		// {
			// ft_printf("RECONSTRUCT PATH\t:\tprev[current->id: %d]: %s, %p\n", current->id, (*prev)[current->id] && (*prev)[current->id]->name ? (*prev)[current->id]->name : NULL, (*prev)[current->id]);
			// ft_printf(YELLOW"RECONSTRUCT PATH\t:\tprev[current->id: %d]: %s, prev[current->id]->id: %d\n", current->id, (*prev)[current->id] ? (*prev)[current->id]->name : NULL, (*prev)[current->id] ? (*prev)[current->id]->id : -1);
			// ft_printf("lem->room_links_arr[current->id][(*prev)[current->id]->id]: %d, lem->room_arr[lem->room_links_arr[current->id][(*prev)[current->id]->id]]->name: %s\n"RESET, (*prev)[current->id] ? lem->room_links_arr[current->id][(*prev)[current->id]->id] : -1, (*prev)[current->id] && lem->room_links_arr[current->id][(*prev)[current->id]->id] != -1 ? lem->room_arr[lem->room_links_arr[current->id][(*prev)[current->id]->id]]->name : NULL);
		// }
		if ((*prev)[current->id] && \
			lem->room_links_arr[current->id][(*prev)[current->id]->id] != -1)
			current = lem->room_arr[lem->room_links_arr\
					[current->id][(*prev)[current->id]->id]];
		else
			current = NULL;
		// if (nb == 2)
		// {
			// if (current)
			// 	ft_printf(BLUE"RECONSTRUCT PATH\t:\tnext current->name: %s, %p\n"RESET, current->name, current);
			// else
			// 	ft_printf(BLUE"CURRENT IS NULL\n"RESET);
		// }
	}
	path = room_arr_reverse(path);
	// ft_printf("path[0]->name: %s, lem->start->name: %s\n", path[0]->name, lem->start->name);
	if (ft_strequ(path[0]->name, lem->start->name))
		return (path);
	free(path);
	return (NULL);
}

t_room			**bfs(t_lem *lem, int nb)
{
	t_room	**prev;
	t_room	**path;
	int		i;

	// ft_printf(BOLD RED"\nNEW BFS ROUND\n\n"RESET);
	prev = solve(lem, nb);
	// for (int i = 0; prev[i]; i++)
	// 	ft_printf(BOLD YELLOW"%s "RESET, path[i]->name);
	path = reconstruct_path(&prev, lem);
	free(prev);
	i = -1;
	while (path && path[++i])
		path[i]->in_path = TRUE;
	return (path);
}
