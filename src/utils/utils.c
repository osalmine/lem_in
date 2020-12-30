/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:27:56 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/31 00:37:55 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// int		room_count(t_lem *lem)
// {
// 	int		counter;
// 	t_list	*tmp;

// 	counter = 0;
// 	tmp = lem->room_list;
// 	while (tmp)
// 	{
// 		counter++;
// 		tmp = tmp->next;
// 	}
// 	return (counter);
// }

unsigned int hash(char *str, int size)
{
	unsigned int hash;
	int c;

	hash = 0;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	hash = hash % size;
	return (hash);
}

int		arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		find_from_que(t_room **que, t_room *room)
{
	int i;

	i = 0;
	while (que[i])
	{
		if (que[i] == room)
			return (1);
		i++;
	}
	return (0);
}

void	free_strsplit(char ***str)
{
	char **curr;

	if (str && *str)
	{
		curr = (*str);
		while (*curr)
			free(*(curr++));
		free(*str);
		*str = NULL;
		str = NULL;
	}
}
