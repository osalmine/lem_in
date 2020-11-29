/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:27:56 by osalmine          #+#    #+#             */
/*   Updated: 2020/11/29 14:07:08 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

int     room_count(t_lem* lem)
{
	int		counter;
	t_list	*tmp;

	counter = 0;
	tmp = lem->room_list;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

char    **create_arr(t_lem *lem, ssize_t size)
{
	char	**que;
	int		i;

	if (size == -1)
		size = lem->room_nb + 1;
	if (!(que = (char**)malloc(sizeof(char*) * size)))
		ft_exit(RED"Malloc error"RESET);
	que[size - 1] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	return (que);
}

t_room	**create_room_arr(t_lem *lem, ssize_t size)
{
	t_room	**que;
	int		i;

	if (size == -1)
		size = lem->room_nb + 1;
	ft_printf(YELLOW"CREATE_ROOM_ARR: malloced size: %d\n"RESET, size);
	if (!(que = (t_room**)malloc(sizeof(t_room*) * size)))
		ft_exit(RED"Malloc error"RESET);
	que[size - 1] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	i = -1;
	while (++i <= size)
		ft_printf("que[%d]: %p\n", i, que[i]);
	ft_printf("Que start addr: %p, size: %d\n", que, sizeof(que) * sizeof(t_room*));
	return (que);
}

void	push_to_room_arr(t_room **arr, t_room *room)
{
	int i;

	i = 0;
	ft_printf("Room to push: %s, %p\n", room->name, room);
	while (arr[i] && arr[i]->name)
	{
		ft_printf("push_to_room_arr: room[%d]->name: %s (%p)\n", i, arr[i]->name, arr[i]);
		i++;
	}
	arr[i] = room;
	ft_printf("arr[%d]: %s, %p\n", i, room->name, room);
}

void	push_to_arr(char **que, char *room)
{
	int i;

	i = 0;
	while (que[i])
		i++;
	que[i] = ft_strdup(room);
}

char	**arr_reverse(char **arr)
{
	char	**new_arr;
	int		count;
	int		start;

	count = 0;
	start = 0;
	while (arr[count])
		count++;
	if (!(new_arr = (char**)malloc(sizeof(char*) * (count + 1))))
		ft_exit(RED"Malloc error"RESET);
	new_arr[count] = NULL;
	while (count)
		new_arr[start++] = ft_strdup(arr[(count--) - 1]);
	free_strsplit(&arr);
	return (new_arr);
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

int		arr_size(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

int		room_arr_size(t_room **arr)
{
	int i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}