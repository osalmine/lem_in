/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:11:08 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/21 19:17:06 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

char	**ft_2dstrdup(char **str)
{
	int		i;
	char	**new_str;

	i = arr_size(str);
	if (!(new_str = (char**)malloc(sizeof(char*) * (i + 1))))
		ft_exit(RED"ERROR: Malloc error"RESET);
	new_str[i] = NULL;
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	return (new_str);
}

int     check_for_dup_path_size_1(t_lem *lem, char **path)
{
	t_list	*paths;
	int		i;
	int		path_len;

	paths = lem->paths_list;
	path_len = arr_size(path) - 1;
	// ft_printf("path_len: %d\n", path_len);
	while (paths && path_len == 1)
	{
		i = 0;
		// ft_printf("LEM PATH LEN: %d, PATH LEN: %d\n", ((t_path*)paths->content)->len, path_len);
		if (((t_path*)paths->content)->len == path_len)
		{
			while (path[i] && ft_strequ(((t_path*)paths->content)->path_arr[i], path[i]))
				i++;
			// ft_printf("i: %d\n", i);
			if (i == path_len + 1)
			{
				// ft_printf("check_for_dup_path_size_1 return 1\n");
				return (1);
			}
		}
		paths = paths->next;
	}
	// ft_printf("check_for_dup_path_size_1 return 0\n");
	return (0);
}

int     check_for_dup_path(t_list *paths_lst, char **path)
{
	t_list	*paths;
	int		i;
	int		path_len;

	paths = paths_lst;
	path_len = arr_size(path) - 1;
	ft_printf(RED"CHECK_FOR_DUP_PATH\n"RESET);
	ft_printf("path to be found: %la\n", path);
	while (paths)
	{
		i = 0;
		// ft_printf("LEM PATH LEN: %d, PATH LEN: %d\n", ((t_path*)paths->content)->len, path_len);
		if (((t_path*)paths->content)->len == path_len)
		{
			while (path[i] && ft_strequ(((t_path*)paths->content)->path_arr[i], path[i]))
				i++;
			ft_printf("i: %d\n", i);
			if (i == path_len + 1)
			{
				ft_printf(BOLD RED"FOUND DUP PATH\n"RESET);
				return (1);
			}
		}
		paths = paths->next;
	}
	return (0);
}

int		min_3(int x, int y, int z)
{
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}