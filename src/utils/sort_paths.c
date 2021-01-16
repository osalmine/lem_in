/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:45:46 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/08 15:53:57 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static void	swap(t_list *a, t_list *b)
{
	void	*content;
	size_t	content_size;

	content = a->content;
	content_size = a->content_size;
	a->content = b->content;
	a->content_size = b->content_size;
	b->content = content;
	b->content_size = content_size;
}

void		sort_paths(t_list *paths)
{
	t_list *lst;
	t_list *next;

	lst = paths;
	while (lst)
	{
		next = lst;
		while (next)
		{
			if (((t_path*)next->content)->len < ((t_path*)lst->content)->len)
				swap(next, lst);
			next = next->next;
		}
		lst = lst->next;
	}
}
