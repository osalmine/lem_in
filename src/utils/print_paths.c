/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:15:05 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/13 15:45:47 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void	print_paths(t_lem *lem, t_list *lem_paths)
{
	t_list	*paths;
	t_path	*path;
	int		i;

	paths = lem_paths;
	ft_putstr("\n");
	while (paths)
	{
		i = 0;
		path = (t_path*)paths->content;
		if (lem->opts.colours)
			ft_putstr(path->colour);
		while (i <= path->len)
		{
			if (i == path->len)
				ft_printf("[%s]", path->path_arr[i]->name);
			else
				ft_printf("[%s]->", path->path_arr[i]->name);
			i++;
		}
		ft_putstr(RESET"\n\n");
		paths = paths->next;
	}
	ft_putstr("\n");
}
