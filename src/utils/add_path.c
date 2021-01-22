/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:12:01 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/21 12:54:59 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static char	*assign_colour(t_list *paths_list)
{
	t_list	*paths;
	char	*tmp;
	char	*colour;
	char	*nb;
	int		i;

	paths = paths_list;
	i = 1;
	while (paths)
	{
		if (i >= 256)
			i = 1;
		else
			i += 10;
		paths = paths->next;
	}
	nb = ft_itoa(i);
	tmp = ft_strjoin("\x1b[38;5;", nb);
	colour = ft_strjoin(tmp, "m");
	ft_strdel(&nb);
	ft_strdel(&tmp);
	return (colour);
}

t_set		*init_set()
{
	t_set *set;

	if (!(set = (t_set*)malloc(sizeof(t_set))))
		ft_exit("ERROR: malloc error");
	set->cost = 0;
	set->flow = 0;
	set->len = 0;
	set->paths = NULL;
	return (set);
}

void		add_path(t_lem *lem, t_room **path, t_list **path_list, t_set **set)
{
	t_path	path_struct;
	// int		i;

	// if (!(*set))
	// 	(*set) = init_set();
	// ft_printf(BOLD BLUE"NEW ADD_PATH\n"RESET);
	// i = -1;
	// while (path && path[++i])
	// {
	// 	if (path[i] == lem->end)
	// 		break ;
	// 	path[i]->in_path = TRUE;
	// }
	path_struct.len = room_arr_size(path) - 1;
	path_struct.path_arr = path;
	path_struct.in_use = TRUE;
	(*set)->len += path_struct.len;
	// ft_printf("set->len: %d\n", (*set)->len);
	// ft_printf("Getting set flow in add_path\n");
	// (*set)->flow = lem->path_amount;
	if (lem->opts.colours)
			path_struct.colour = assign_colour((*set)->paths);
	else
		path_struct.colour = NULL;
	ft_lstaddlast(&(*path_list), ft_lstnew(&path_struct, sizeof(t_path)));
}
