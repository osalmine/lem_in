/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:13:34 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/27 11:16:48 by osalmine         ###   ########.fr       */
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

static void	turn_loop(t_lem *lem, t_room *end)
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
				next_room = find_room(cur_ant->path->path_arr[cur_ant->move_nb + 1], lem);
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
		}
		i++;
		ant_list = ant_list->next;
		reset_turn(lem);
	}
	ft_putchar('\n');
	lem->moves_count++;
}

void		guide_ants(t_lem *lem)
{
	t_room  *start;
	t_room	*end;

	if (!(start = find_room_by_type(START, lem)))
		ft_exit(RED"ERROR: No start room (guide_ants)"RESET);
	if (!(end = find_room_by_type(END, lem)))
		ft_exit(RED"ERROR: No end room (guide_ants)"RESET);
	find_paths(lem, start, end);
	assign_paths(lem, start);
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
		// t_list	*tmp_ant;

		// tmp_ant = lem->ants;
		// while (tmp_ant)
		// {
			// ft_printf(CYAN"Ant id: %d\n"RESET, ((t_ant*)tmp_ant->content)->id);
			// tmp_ant = tmp_ant->next;
		// }
		turn_loop(lem, end);
		// ft_printf("%send node %sant amount: %d, ant amount: %d\n"RESET, RED, BLUE, end->has_ant, lem->ant_nb);
	}
}