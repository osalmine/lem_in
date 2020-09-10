/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/09 16:49:05 by osalmine         ###   ########.fr       */
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
	if ((link->flow == INF || link->flow == -1) && next->type != END)
		check = 1;
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
			// ft_printf("found from path: %s\n", (find_in_path(lem, neighbor, end) ? "TRUE" : "FALSE"));
			can_use_link = check_for_flow(lem, node, neighbor);
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && (can_use_link || !find_in_path(lem, neighbor, end)))
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
					// ft_printf(CYAN"%s "RESET, prev[j++]);
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
	// ft_printf("len: %d\n", len - 1);
	if (!(path_struct = (t_path*)malloc(sizeof(t_path))))
		ft_exit(RED"ERROR: Malloc error"RESET);
	path_struct->len = len - 1;
	// ft_printf("BEFORE PATH DUP: %la\n", path);
	path_struct->path_arr = ft_2dstrdup(path);
	path_struct->colour = assign_colour(lem);
	// ft_printf("AFTER PATH DUP: %la\n", path_struct->path_arr);
	ft_lstaddlast(&lem->paths_list, ft_lstnew(path_struct, sizeof(t_path)));
}

static void	assign_flows(t_lem *lem, char **path)
{
	int		i;
	t_link	*link;

	i = 0;
	ft_printf(RED BOLD"NEW ASSIGN\n"RESET);
	while (path[i + 1])
	{
		if (!(link = find_link(lem, path[i], path[i + 1])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		if (link->flow == INF)
			link->flow = 1;
		else
			link->flow--;
		if (!(link = find_link(lem, path[i + 1], path[i])))
			ft_exit(RED"ERROR: couldn't find link\n"RESET);
		if (link->flow == INF)
			link->flow = -1;
		else
			link->flow++;
		i++;
	}
}

void        find_paths(t_lem *lem, t_room *start, t_room *end)
{
    char **path;

	while ((path = bfs(start, end, lem)))
	{
		if (!path)
			break ;
		assign_flows(lem, path);
		t_list *links;
		t_link *link;
		links = lem->link_list;
		while (links)
		{
			link = (t_link*)links->content;
			ft_printf("LINK: room1: %s, room2: %s, flow: %d\n", link->room1, link->room2, link->flow);
			links = links->next;
		}
		// ft_printf("Path: %la\n", path);
		add_path(lem, path);
		free_strsplit(&path);
		reset_rooms(lem);
	}
	// ft_printf(RED BOLD UNDERLINE"FOUND ALL PATHS\n"RESET);
	if (!lem->paths_list)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts->paths)
		print_paths(lem);
}