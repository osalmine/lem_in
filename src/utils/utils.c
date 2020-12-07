/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 14:27:56 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/06 21:14:45 by osalmine         ###   ########.fr       */
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
		size = lem->room_count + 1;
	if (!(que = (char**)malloc(sizeof(char*) * size)))
		ft_exit(RED"ERROR: Malloc error"RESET);
	// ft_printf("create_arr, que: %p\n", que);
	// if (sizeof(char*) * size == 16)
	// 		ft_printf(RED"create_arr: sizeof(char*) * size IS 16\n"RESET);
	// que[size - 1] = NULL;
	i = 0;
	while (i < size)
		que[i++] = NULL;
	// i = -1;
	// while (++i < size)
	// 	ft_printf("CREATE ARR: que[%d]: %p\n", i, que[i]);
	return (que);
}

void	push_to_arr(char **que, char *room)
{
	int i;

	i = 0;
	while (que[i])
		i++;
	que[i] = ft_strdup(room);
	// ft_printf("push_to_arr, que[%d]: %p\n", i, que[i]);
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
	// ft_printf("arr_reverse, new_arr: %p\n", new_arr);
	// if (sizeof(char*) * (count + 1) == 16)
	// 		ft_printf(RED"arr_reverse: sizeof(char*) * (count + 1) IS 16\n"RESET);
	new_arr[count] = NULL;
	while (count)
	{
		new_arr[start] = ft_strdup(arr[(count--) - 1]);
		// ft_printf("arr_reverse, new_arr[%d]: %p\n", start, new_arr[start]);
		start++;
	}
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