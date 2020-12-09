/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/07 20:35:13 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	reset_turn(t_lem *lem)
{
	// t_room	*prev_room;
	t_ant	*cur_ant;
	t_list	*ant_list;

	ant_list = lem->ants;
	// ft_printf(BG_RED"Reset turn"RESET);
	// write(1, "\n", 1);
	while (ant_list)
	{
		cur_ant = (t_ant*)ant_list->content;
		// ft_printf("cur_ant: %d, has_moved: %s\n", cur_ant->id, (cur_ant->has_moved ? "TRUE" : "FALSE"));
		if (cur_ant->has_moved)
		{
			// prev_room = find_room(cur_ant->path[cur_ant->move_nb - 1], lem);
			// prev_room->has_ant = FALSE;
			cur_ant->has_moved = FALSE;
		}
		ant_list = ant_list->next;
	}
}

static void	turn_loop(t_lem *lem)
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
			// if (!cur_ant->path)
			// 	cur_ant->path = bfs(start, end, lem);
			if (cur_ant->path == NULL && cur_ant->id == 1)
				ft_exit(RED"ERROR: No path found"RESET);
			// if (cur_ant->path == NULL)
			// 	ft_printf(RED"No path found\n"RESET);
			// else
			// 	ft_printf(BLUE"SHORTEST PATH: %la\n"RESET, cur_ant->path);
			if (cur_ant->path != NULL)
			{
				if (!cur_ant->path->path_arr[cur_ant->move_nb + 1] || !cur_ant->path->path_arr[cur_ant->move_nb + 1]->name || !(next_room = find_room(cur_ant->path->path_arr[cur_ant->move_nb + 1]->name, lem)))
					ft_exit(RED"ERROR: room not found (turn_loop)"RESET);
				if (!next_room->has_ant || next_room->type == END)
				{
					cur_ant->room->has_ant = FALSE;
					cur_ant->room = next_room;
					if (lem->opts->colours)
						ft_printf("%sL%d-%s "RESET, cur_ant->path->colour, cur_ant->id, cur_ant->room->name);
					else
						ft_printf("L%d-%s ", cur_ant->id, cur_ant->room->name);
					if (cur_ant->room->type == NORMAL)
						cur_ant->room->has_ant = TRUE;
					cur_ant->has_moved = TRUE;
					cur_ant->move_nb++;
					if (cur_ant->room->type == END)
					{
						// ft_printf(BG_CYAN BLACK"ANT %d REACHED END"RESET, cur_ant->id);
						// write(1, "\n", 1);
						lem->end->has_ant++;
					}
				}
			}
		}
		i++;
		ant_list = ant_list->next;
		reset_turn(lem);
	}
	ft_putchar('\n');
	lem->moves_count++;
}

// static int	max_flow(t_lem *lem)
// {
// 	t_list	*links;
// 	int		start_links;
// 	int		end_links;

// 	start_links = 0;
// 	end_links = 0;
// 	links = lem->start->links;
// 	while (links)
// 	{
// 		start_links++;
// 		links = links->next;
// 	}
// 	links = lem->end->links;
// 	while (links)
// 	{
// 		end_links++;
// 		links = links->next;
// 	}
// 	return (min_3(lem->ant_nb, start_links, end_links));
// }

void		guide_ants(t_lem *lem)
{
	find_paths(lem);
	assign_paths(lem);
	while (lem->end->has_ant != lem->ant_nb)
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
		// t_list	*tmp_ant;

		// tmp_ant = lem->ants;
		// while (tmp_ant)
		// {
			// ft_printf(CYAN"Ant id: %d\n"RESET, ((t_ant*)tmp_ant->content)->id);
			// tmp_ant = tmp_ant->next;
		// }
		turn_loop(lem);
		// ft_printf("%send node %sant amount: %d, ant amount: %d\n"RESET, RED, BLUE, end->has_ant, lem->ant_nb);
	}
}