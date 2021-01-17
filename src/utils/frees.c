/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:04:20 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/17 13:18:36 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	free_path(void *path, size_t size)
{
	size = 0;
	ft_memdel((void**)(&((t_path*)path)->path_arr));
	ft_strdel(&((t_path*)path)->colour);
	ft_memdel((void**)&path);
}

void		free_set(t_set **set)
{
	if ((*set)->paths)
	{
		ft_lstdel(&(*set)->paths, free_path);
		ft_memdel((void**)&(*set)->paths);
	}
	ft_memdel((void**)&(*set));
}