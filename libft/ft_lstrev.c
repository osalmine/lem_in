/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:54:26 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 12:05:29 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **list)
{
	t_list	*head;
	t_list	*tmp;
	t_list	*prev;

	head = *list;
	tmp = NULL;
	while (head)
	{
		prev = tmp;
		tmp = head;
		head = head->next;
		tmp->next = prev;
	}
	*list = tmp;
}
