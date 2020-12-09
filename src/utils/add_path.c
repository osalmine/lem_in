/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:12:01 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/09 23:08:32 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static char *assign_colour(t_lem *lem)
{
	t_list	*paths;
	char	*tmp;
	char	*colour;
	char	*nb;
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
	nb = ft_itoa(i);
	tmp = ft_strjoin("\x1b[38;5;", nb);
	colour = ft_strjoin(tmp, "m");
	ft_strdel(&nb);
	ft_strdel(&tmp);
	return (colour);
}

void        add_path(t_lem *lem, t_room **path, t_list **path_list)
{
	t_path	path_struct;

	// if (!(path_struct = (t_path*)malloc(sizeof(t_path))))
	// 	ft_exit(RED"ERROR: Malloc error"RESET);
	path_struct.len = room_arr_size(path) - 1;
	path_struct.path_arr = path;
	path_struct.in_use = TRUE;
	if (lem->opts->colours)
		path_struct.colour = assign_colour(lem);
	else 
		path_struct.colour = NULL;
	ft_lstaddlast(&(*path_list), ft_lstnew(&path_struct, sizeof(t_path)));
}