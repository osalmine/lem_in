/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/22 16:32:25 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int	check_for_flow(t_lem *lem, t_room *current, t_room *next)
{
	int		check;
	t_link	*link;

	check = 0;
	if (!(link = find_link(lem, current->name, next->name)))
		ft_exit(RED"ERROR: can't find link (check_for_flow)"RESET);
	if (link->flow == INF || link->flow == -1)
		check = 1;
	// ft_printf("room1: %s, room2: %s, flow: %d, check: %d\n", link->room1, link->room2, link->flow, check);
	return (check);
}

static char	**solve(t_room *start, t_room *end, t_lem *lem)
{
	char	**prev;
	char	**que;
	t_room	*node;
	t_room	*neighbor;
	t_link	*path;
	t_list	*tmp;
	int		i;
	int		can_use_link;

	i = 0;
	que = create_arr(lem, -1);
	prev = create_arr(lem, -1);
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
			// ft_printf("found from path: %s\n"RESET, (find_in_path(lem->paths_bef_ek, neighbor, end) ? "TRUE" : "FALSE"));
			can_use_link = check_for_flow(lem, node, neighbor);
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && ((can_use_link || !find_in_path(lem->paths_bef_ek, neighbor, end)) && (!can_use_link ? neighbor->type != END : TRUE)))
			{
				push_to_arr(que, neighbor->name);
				// ft_printf(YELLOW"SOLVE\t\t:\tpushed %s to que: %la\n"RESET, neighbor->name, que);
				neighbor->visited = TRUE;
				prev[neighbor->id] = ft_strdup(node->name);
				// ft_printf(BLUE"Pushed %s to prev at id: %d : %s\n"RESET, node->name, neighbor->id, prev[neighbor->id]);
				// ft_printf(BG_CYAN WHITE"FULL PREV ARRAY IN SOLVE:"RESET);
				// ft_putchar('\n');
				// int j = 0;
				// int s = room_count(lem);
				// while (j < s)
				// 	ft_printf(CYAN"%s "RESET, prev[j++]);
				// ft_putchar('\n');
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

static char **reconstruct_path(t_room *start, t_room* end, char **prev, t_lem *lem)
{
	char	**path;
	t_room	*current;

	path = create_arr(lem, -1);
	current = end;
	// ft_printf(BG_CYAN WHITE"FULL PREV ARRAY IN RECONSTRUCT_PATH:"RESET);
	// ft_putchar('\n');
	// int j = 0;
	// int s = room_count(lem);
	// while (j < s)
	// 	ft_printf(CYAN"%s "RESET, prev[j++]);
	// ft_putchar('\n');
	while (current != NULL)
	{
		// ft_printf(CYAN"RECONSTRUCT PATH\t:\tcurrent->name: %s\n"RESET, current->name);
		push_to_arr(path, current->name);
		// ft_printf("RECONSTRUCT PATH\t:\tprev[current->id: %d]: %s\n", current->id, prev[current->id]);
		current = find_room(prev[current->id], lem);
		// if (current)
		// 	ft_printf(BLUE"RECONSTRUCT PATH\t:\tnext current->name: %s\n"RESET, current->name);
		// else
		// 	ft_printf(BLUE"CURRENT IS NULL\n"RESET);
	}
	path = arr_reverse(path);
	// ft_printf("PATH: %la\n", path);
	if (ft_strequ(path[0], start->name))
		return (path);
	return (NULL);
}

static char	**bfs(t_room *start, t_room *end, t_lem *lem)
{
	char 	**prev;
	char 	**path;

	prev = solve(start, end, lem);
	path = reconstruct_path(start, end, prev, lem);
	free_strsplit(&prev);
	return (path);
}

static char	**ft_2dstrdup(char **str)
{
	int		i;
	char	**new_str;

	i = arr_size(str);
	if (!(new_str = (char**)malloc(sizeof(char*) * (i + 1))))
		ft_exit(RED"ERROR: Malloc error"RESET);
	new_str[i] = NULL;
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	return (new_str);
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

static char *assign_colour(t_lem *lem)
{
	t_list	*paths;
	char	*tmp;
	char	*colour;
	int		i;

	paths = lem->paths_list;
	i = 1;
	while (paths)
	{
		if (i >= 256)
			i = 1;
		else
			i += 10;
		paths = paths->next;
	}
	tmp = ft_strjoin("\x1b[38;5;", ft_itoa(i));
	colour = ft_strjoin(tmp, "m");
	ft_strdel(&tmp);
	return (colour);
}

static void add_path(t_lem *lem, char **path)
{
    int		len;
	t_path	*path_struct;

	len = 0;
	while (path[len])
		len++;
	if (!(path_struct = (t_path*)malloc(sizeof(t_path))))
		ft_exit(RED"ERROR: Malloc error"RESET);
	path_struct->len = len - 1;
	path_struct->path_arr = ft_2dstrdup(path);
	if (lem->opts->colours)
		path_struct->colour = assign_colour(lem);
	ft_lstaddlast(&lem->paths_list, ft_lstnew(path_struct, sizeof(t_path)));
}

static void	assign_flows(t_lem *lem, char **path)
{
	int		i;
	t_link	*link;

	i = 0;
	// ft_printf(RED BOLD"NEW ASSIGN\n"RESET);
	while (path[i + 1])
	{
		// ft_printf("path[%d]: %s, path[%d + 1]: %s\n", i, path[i], i, path[i + 1]);
		if (!(link = find_link(lem, path[i], path[i + 1])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		// ft_printf("Link (%s-%s) flow prev assign: %d\n", link->room1, link->room2, link->flow);
		if (link->flow == INF)
			link->flow = 1;
		else
			link->flow++;
		// ft_printf("Link (%s-%s) flow after assign: %d\n", link->room1, link->room2, link->flow);
		if (!(link = find_link(lem, path[i + 1], path[i])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		// ft_printf("Link (%s-%s) flow prev assign: %d\n", link->room1, link->room2, link->flow);
		if (link->flow == INF)
			link->flow = -1;
		else
			link->flow--;
		// ft_printf("Link (%s-%s) flow after assign: %d\n", link->room1, link->room2, link->flow);
		i++;
	}
}

static int	check_for_dup_path(t_lem *lem, char **path)
{
	t_list	*paths;
	int		i;
	int		path_len;

	paths = lem->paths_list;
	path_len = arr_size(path) - 1;
	// ft_printf("path_len: %d\n", path_len);
	while (paths && path_len == 1)
	{
		i = 0;
		// ft_printf("LEM PATH LEN: %d, PATH LEN: %d\n", ((t_path*)paths->content)->len, path_len);
		if (((t_path*)paths->content)->len == path_len)
		{
			while (path[i] && ft_strequ(((t_path*)paths->content)->path_arr[i], path[i]))
				i++;
			// ft_printf("i: %d\n", i);
			if (i == path_len + 1)
				return (1);
		}
		paths = paths->next;
	}
	return (0);
}

static char	**ek_find_path(t_lem *lem)
{
	char	**path;
	t_room	*current;
	t_room	*next;
	t_list	*links;
	int		i;

	i = 0;
	reset_rooms(lem);
	path = create_arr(lem, -1);
	current = find_room_by_type(START, lem);
	push_to_arr(path, current->name);
	current->visited = TRUE;
	t_list *paths;
	paths = lem->paths_list;
	while (paths)
	{
		// ft_printf("%la, len: %d\n", ((t_path*)(paths->content))->path_arr, ((t_path*)(paths->content))->len);
		paths = paths->next;
	}
	while (path[i])
	{
		// ft_printf("path[%d]: %s\n", i, path[i]);
		links = current->links;
		while (links)
		{
			// ft_printf("flow: %d, room1: %s, room2: %s\n", find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2);
			if (find_link(lem, ((t_link*)links->content)->room1, ((t_link*)links->content)->room2)->flow == 1)
			{
				next = find_room(((t_link*)links->content)->room2, lem);
				// ft_printf("Next name: %s\n", next->name);
				if (!next->visited && !find_in_path(lem->paths_list, next, find_room_by_type(END, lem)))
				{
					// ft_printf("Ok\n");
					current = next;
					current->visited = TRUE;
					push_to_arr(path, current->name);
					break ;
				}
			}
			links = links->next;
		}
		i++;
	}
	// ft_printf(BLUE"PATH: %la\n"RESET, path);
	if (!check_for_dup_path(lem, path) && ft_strequ(path[arr_size(path) - 1], (find_room_by_type(END, lem))->name))
		return (path);
	return (NULL);
}

static void	flows_pathfinder(t_lem *lem)
{
	char **path;

	while ((path = ek_find_path(lem)))
	{
		add_path(lem, path);
		free_strsplit(&path);
	}
}

static void	assign_weights(t_lem *lem, char **path)
{
	int		i;
	t_room	*room;

	i = 0;
	while (path[i])
	{
		room = find_room(path[i], lem);
		// ft_printf("ASSIGN WEIGHTS ROOM: %s", room->name);
		if (room->type == END)
			room->weight = INF;
		else
			room->weight = i;
		// ft_printf(", WEIGHT: %d\n", room->weight);
		i++;
	}
}

void        find_paths(t_lem *lem, t_room *start, t_room *end)
{
    char	**path;
	t_path	*path_struct;

	start->weight = 0;
	while ((path = bfs(start, end, lem)))
	{
		if (!path)
			break ;
		assign_weights(lem, path);
		assign_flows(lem, path);
		// ft_printf(BOLD RED"Path: %la\n\n"RESET, path);
		if (lem->ant_nb == 1)
		{
			add_path(lem, path);
			free_strsplit(&path);
		}
		else
		{
			if (!(path_struct = (t_path*)malloc(sizeof(t_path))))
				ft_exit(RED"ERROR: Malloc error"RESET);
			path_struct->path_arr = ft_2dstrdup(path);
			ft_lstaddlast(&lem->paths_bef_ek, ft_lstnew(path_struct, sizeof(t_path)));

		}
		// t_list *pths;
		// pths = lem->paths_bef_ek;
		// while (pths)
		// {
		// 	ft_printf("PATH IN PATHS_BEF_EK: %la\n", ((t_path*)pths->content)->path_arr);
		// 	pths = pths->next;
		// }
		reset_rooms(lem);
	}
	// t_list *links;
	// t_link *link;
	// links = lem->link_list;
	// while (links)
	// {
	// 	link = (t_link*)links->content;
	// 	ft_printf("LINK: room1: %s, room2: %s, flow: %d\n", link->room1, link->room2, link->flow);
	// 	links = links->next;
	// }
	if (lem->ant_nb != 1)
		flows_pathfinder(lem);
	sort_paths(lem);
	// ft_printf(RED BOLD UNDERLINE"FOUND ALL PATHS\n"RESET);
	if (!lem->paths_list)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts->paths)
		print_paths(lem);
}