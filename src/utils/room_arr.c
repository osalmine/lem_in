/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:46:45 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/21 11:47:53 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

t_room	**create_room_arr(t_lem *lem, ssize_t size)
{
	t_room	**que;
	int		i;

	if (size == -1)
		size = lem->room_count + 1;
	if (!(que = (t_room**)malloc(sizeof(t_room*) * size)))
		ft_exit(RED"Malloc error"RESET);
	que[size - 1] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	i = -1;
	return (que);
}

void	push_to_room_arr(t_room **arr, t_room *room)
{
	int i;

	i = 0;
	while (arr[i] && arr[i]->name)
		i++;
	arr[i] = room;
}

t_room	**room_arr_reverse(t_room **arr)
{
	t_room	**new_arr;
	int		count;
	int		start;

	count = 0;
	start = 0;
	while (arr[count])
		count++;
	if (!(new_arr = (t_room**)malloc(sizeof(t_room*) * (count + 1))))
		ft_exit(RED"Malloc error"RESET);
	new_arr[count] = NULL;
	while (count)
		new_arr[start++] = arr[(count--) - 1];
	free(arr);
	return (new_arr);
}

int		room_arr_size(t_room **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
