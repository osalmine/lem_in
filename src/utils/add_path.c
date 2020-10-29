/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:12:01 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/21 19:15:47 by osalmine         ###   ########.fr       */
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

void        add_path(t_lem *lem, char **path, t_list **path_list)
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
	path_struct->in_use = TRUE;
	if (lem->opts->colours)
		path_struct->colour = assign_colour(lem);
	else 
		path_struct->colour = NULL;
	ft_lstaddlast(&(*path_list), ft_lstnew(path_struct, sizeof(t_path)));
}