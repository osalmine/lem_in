/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:12:01 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/25 16:08:57 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

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

void        add_path(t_lem *lem, char **path)
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
	else 
		path_struct->colour = NULL;
	ft_lstaddlast(&lem->paths_list, ft_lstnew(path_struct, sizeof(t_path)));
}