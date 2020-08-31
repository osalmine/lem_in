/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/31 15:26:41 by osalmine         ###   ########.fr       */
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

static char **create_arr(t_lem *lem, ssize_t size)
{
	char	**que;
	int		i;

	if (size == -1)
		size = room_count(lem) + 1;
	// ft_printf(RED"room_nb: %d\n", room_nb);
	if (!(que = (char**)malloc(sizeof(char*) * size)))
		ft_exit(RED"Malloc error"RESET);
	que[size] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	// i = 0;
	// while (i < size)
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

static int  find_in_path(t_lem *lem, t_room *room, t_room *end)
{
    t_list	*paths;
	t_path	*cur_path;
	char	**tmp;
	int		i;

	paths = lem->paths_list;
	// ft_putchar('\n');
	// ft_printf(BG_BLUE BLACK"FIND_IN_PATH"RESET);
	// ft_putchar('\n');
	if (room == end)
	{
		// ft_printf("ROOM IS END ROOM\n");
		return (0);
	}
	while (paths)
	{
		i = 0;
		cur_path = (t_path*)paths->content;
		tmp = cur_path->path_arr;
		// ft_printf("path: %la\n", tmp);
		while (tmp[i])
		{
			// ft_printf("tmp[%d]: %s, room->name: %s\n", i, tmp[i], room->name);
			if (ft_strequ(tmp[i], room->name))
				return (1);
			i++;
		}
		// ft_printf("find_in_path after tmp while, i: %d\n", i);
		paths = paths->next;
	}
	// ft_printf("Returning 0 from find_in_path\n");
	return (0);
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
			if (!neighbor->visited && !find_from_que(que, neighbor->name) && !find_in_path(lem, neighbor, end))
			{
				push_to_arr(que, neighbor->name);
				// ft_printf(YELLOW"SOLVE\t\t:\tpushed %s to que: %la\n"RESET, neighbor->name, que);
				neighbor->visited = TRUE;
				prev[neighbor->id] = ft_strdup(node->name);
				// ft_printf(BLUE"Pushed %s to prev at id: %d : %s\n"RESET, node->name, neighbor->id, prev[neighbor->id]);
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_strsplit(&que);
	// ft_printf(BG_WHITE BLACK"RETURN SOLVE"RESET);
	// ft_putchar('\n');
	// ft_printf(GREEN"PREV[0]: %s\n"RESET, prev[0]);
	return (prev);
}

static char **reconstruct_path(t_room *start, t_room* end, char **prev, t_lem *lem)
{
	char	**path;
	t_room	*current;

	path = create_arr(lem, -1);
	current = end;
	// ft_printf("prev[0] is %s\n", prev[0]);
	prev[0] = ft_strdup(start->name);
	// ft_printf("prev[0] is %s\n", prev[0]);
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
	// t_list	*tmp;

	// tmp = lem->ants;
	// while (tmp)
	// {
	// 	t_ant *ant = (t_ant*)tmp->content;
	// 	ft_printf("Ant id: %d\n", ant->id);
	// 	tmp = tmp->next;
	// }
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
	// ft_printf("PATH SIZE: %d\n", i);
	if (!(new_str = (char**)malloc(sizeof(char*) * (i + 1))))
		ft_exit(RED"ERROR: Malloc error"RESET);
	new_str[i] = NULL;
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	// ft_printf(RED"2DSTRDUP NEW: %la\n"RESET, new_str);
	return (new_str);
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
	// ft_printf("AFTER PATH DUP: %la\n", path_struct->path_arr);
	ft_lstaddlast(&lem->paths_list, ft_lstnew(path_struct, sizeof(t_path)));
	// t_list *pth_lst;
	// pth_lst = lem->paths_list;
	// ft_printf("Printing all paths\n");
	// while (pth_lst)
	// {
	// 	ft_printf("pth_lst arr: %la\n", ((t_path*)pth_lst->content)->path_arr);
	// 	pth_lst = pth_lst->next;
	// }
}

void        find_paths(t_lem *lem, t_room *start, t_room *end)
{
    char **path;

	while ((path = bfs(start, end, lem)))
	{
		if (!path)
		{
			// ft_printf("No path found!\n");
			break ;
		}
		// ft_printf("Path: %la\n", path);
		add_path(lem, path);
		free_strsplit(&path);
		reset_rooms(lem);
	}
	// ft_printf(RED BOLD UNDERLINE"FOUND ALL PATHS\n"RESET);
	if (!lem->paths_list)
		ft_exit(RED"ERROR: No paths found"RESET);
	// t_list *tmp;
	// tmp = lem->paths_list;
	// while (tmp)
	// {
	// 	ft_printf("Path: %la, length: %d\n", ((t_path*)tmp->content)->path_arr, ((t_path*)tmp->content)->len);
	// 	tmp = tmp->next;
	// }
	print_paths(lem);
}