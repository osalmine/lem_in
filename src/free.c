/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:03:56 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/16 21:04:13 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

void	free_strsplit(char ***str)
{
	char **curr;

	if (str && *str)
	{
		curr = (*str);
		while (*curr)
			free(*(curr++));
		free(*str);
		str = NULL;
	}
}