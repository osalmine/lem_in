/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/03/19 21:09:15 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_H

# define LEM_H

# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>

# define NORMAL	0;
# define START	1;
# define END	2;

typedef struct	s_path
{
	char	*room1;
	char	*room2;
}				t_path;

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		has_ant;
	int		type;
}				t_room;

typedef struct	s_ant
{
	int		id;
	t_room	*room;
}				t_ant;

typedef struct	s_lem
{
	int		ant_nb;
	t_ant	*ants;
}				t_lem;

t_lem	*lem_init(int ac, char **av);

#endif
