/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:07:32 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/31 16:31:22 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words(const char *s, char c)
{
	int words;
	int i;

	words = 0;
	i = 0;
	if (s[i] != c && s[i])
	{
		i++;
		words++;
	}
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			if (s[i] != c && s[i])
				words++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (words);
}
