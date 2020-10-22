/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:27:56 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/07 14:31:16 by osalmine         ###   ########.fr       */
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
		size = room_count(lem) + 1;
	if (!(que = (char**)malloc(sizeof(char*) * size)))
		ft_exit(RED"Malloc error"RESET);
	que[size - 1] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	return (que);
}

void	push_to_arr(char **que, char *room)
{
	int i;

	i = 0;
	while (que[i])
		i++;
	que[i] = ft_strdup(room);
}

char    **arr_reverse(char **arr)
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

int	arr_size(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}