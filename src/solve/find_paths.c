/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:25:46 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/16 11:45:49 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void		reset_rooms_bfs(t_lem *lem)
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

void		reset_rooms_ek(t_lem *lem)
{
	t_list	*tmp;
	t_room	*room;

	tmp = lem->room_list;
	while (tmp)
	{
		room = (t_room*)tmp->content;
		room->visited_ek = FALSE;
		tmp = tmp->next;
	}
}

static void	new_best_set(t_lem *lem)
{
	if (lem->best_set)
		ft_memdel((void**)&lem->best_set);
	if (!(lem->best_set = (t_set*)malloc(sizeof(t_set))))
		ft_exit("ERROR: malloc error");
	lem->best_set->cost = lem->ek_set->cost;
	// ft_printf("Setting best_set flow from ek_set\n");
	lem->best_set->flow = lem->ek_set->flow;
	lem->best_set->len = lem->ek_set->len;
	lem->best_set->paths = lem->ek_set->paths;
	// ft_printf("lem->best_set->paths: %p\n", lem->best_set->paths);
}

static int	bfs_loop(t_lem *lem, t_room **path)
{
	lem->path_amount++;
	// ft_printf(RED"BFS_LOOP\n"RESET);
	// int i;
	// for (i = 0; path && path[i]; i++)
	// 	ft_printf(BOLD YELLOW"%s "RESET, path[i]->name);
	// ft_printf("LEN: %d\n", i - 1);
	// ft_printf("path: %p\n", path);

	if (!path)
		return (1);
	// assign_weights(lem, path);
	assign_flows(path);
	// t_list *links;
	// links = lem->link_list;
	// while (links)
	// {
	// 	ft_printf("link: %s-%s flow: %d\n", ((t_link*)links->content)->room1->name, ((t_link*)links->content)->room2->name, ((t_link*)links->content)->flow);
	// 	links = links->next;
	// }
	if (!lem->cur_set)
		lem->cur_set = init_set();
	// if (lem->ant_nb == 1)
	// {
		add_path(lem, path, &(lem->cur_set->paths), &lem->cur_set);
	// 	return (1);
	// }
	// t_list *cur_lst;
	// cur_lst = lem->cur_set->paths;
	// ft_printf(BOLD BLUE"ALL FOUND BFS PATHS\n"RESET);
	// while (cur_lst)
	// {
	// 	for (int i = 0; ((t_path*)cur_lst->content)->path_arr && ((t_path*)cur_lst->content)->path_arr[i]; i++)
	// 		ft_printf(BOLD CYAN"%s "RESET, ((t_path*)cur_lst->content)->path_arr[i]->name);
	// 	ft_printf("\n\n");
	// 	cur_lst = cur_lst->next;
	// }
	// if (lem->ant_nb != 1)
		flows_pathfinder(lem);
	if (lem->ek_set->paths)
	{
		sort_paths(lem->ek_set->paths);
		// t_list *ek_lst;
		// ek_lst = lem->ek_set->paths;
		// while (ek_lst)
		// {
		// 	for (int i = 0; ((t_path*)ek_lst->content)->path_arr && ((t_path*)ek_lst->content)->path_arr[i]; i++)
		// 		ft_printf(BOLD WHITE"%s "RESET, ((t_path*)ek_lst->content)->path_arr[i]->name);
		// 	ft_printf("\n\n");
		// 	ek_lst = ek_lst->next;
		// }
		// ft_printf("Getting ek_set flow in bfs_loop\n");
		// lem->ek_set->flow = lem->path_amount;
		lem->ek_set->cost = ((lem->ek_set->len + lem->ant_nb) / lem->ek_set->flow) - 1;
		// else
		// 	lem->cur_set->cost = ((lem->cur_set->len + lem->ant_nb) / 1) - 1;
		// if (lem->best_set)
		// 	ft_printf("Best set cost: %d, flow: %d\n", lem->best_set->cost, lem->best_set->flow);
		// ft_printf("ek_set cost: %d, flow: %d\n", lem->ek_set->cost, lem->ek_set->flow);
		// else
		// 	add_path(lem, path, &(lem->paths_bef_ek));
		if (lem->best_set == NULL || lem->best_set->cost > lem->ek_set->cost)
		{
			// ft_printf(REVERSED"New set assignment"RESET);
			// ft_printf("\n");
			new_best_set(lem);
		}
	}
	// ft_printf("\n\n");
	reset_rooms_bfs(lem);
	ft_memdel((void**)&lem->ek_set);
	// ft_memdel((void**)&path);
	// ft_printf("Returning 0\n");
	return (0);
}

void		find_paths(t_lem *lem, int nb)
{
	t_room	**path;
	int		breaking;

	// lem->start->weight = 0;
	while ((path = bfs(lem, nb)) || TRUE)
		if ((breaking = bfs_loop(lem, path)) == 1)
			break ;
	// if (nb == 1)
	// else
	// 	sort_paths(lem->paths_list2);
	if (!lem->best_set)
		ft_exit(RED"ERROR: No paths found"RESET);
	if (lem->opts.paths && nb == 1)
		print_paths(lem, lem->best_set->paths);
	// if (lem->opts.paths && nb == 2)
	// {
	// 	ft_printf("----------------------\n");
	// 	print_paths(lem, lem->paths_list2);
	// }
}
