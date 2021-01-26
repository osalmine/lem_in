/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:27:56 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 13:59:13 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

unsigned int	hash(char *str, int size)
{
	unsigned int	hash;
	int				c;

	hash = 0;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	hash = hash % size;
	return (hash);
}

int				arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int				find_from_que(t_room **que, t_room *room)
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

void			str_append(char **lines, char *append)
{
	char *tmp;

	tmp = ft_strjoin(*lines, append);
	ft_memdel((void**)lines);
	*lines = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
}
