/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/20 21:20:59 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_H

# define LEM_H

# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>

# ifndef TRUE_FALSE
#  define TRUE_FALSE

#  define TRUE	1
#  define FALSE	0

# endif

# define NORMAL	0
# define START	1
# define END	2

/*
**	Struct for options
**	debug: set to TRUE (=1) for debugging
*/

typedef struct	s_options
{
	int	debug;
}				t_opts;

/*
**	Struct to see to what the room is connected to
**	room1: first door
**	room2: second door
*/

typedef struct	s_path
{
	char	*room1;
	char	*room2;
}				t_path;

/*
**	Struct for each room
**	name: room's name
**	visited: if the room has been visited by the search algo that turn
**	x: x-coordiante
**	y: y-coordinate
**	has_ant: TRUE (=1) if room has ant, else FALSE (=0)
**	type: room's type. START (=1) if room is starting room, END (=2) if room is goal room, else NORMAL (=0)
**	path: previous and next room based on t_path struct
*/

typedef struct	s_room
{
	char	*name;
	int		visited;
	int		x;
	int		y;
	int		has_ant;
	int		type;
	t_list	*paths;
}				t_room;

/*
**	Struct for each ant
**	id: ant's id
**	has_moved: TRUE (=1) if ant has moved that turn, else FALSE (=0)
**	room: ant's current room
*/

typedef struct	s_ant
{
	int		id;
	int		has_moved;
	t_room	*room;
}				t_ant;

/*
**	t_lem: main struct
**	ant_nb: total ant amount
**	ants: list of all ants represented as t_ant struct
**	room_list: list of all rooms represented as t_room struct
**	opts: options struct
*/

typedef struct	s_lem
{
	int		ant_nb;
	t_list	*ants;
	t_list	*room_list;
	t_opts	*opts;
}				t_lem;

t_lem	*lem_init(int ac, char **av);
void	lem_flags(t_lem *lem, int ac, char **av);
void	lem_read(t_lem *lem);
void	free_strsplit(char ***str);
t_room  *find_room(char *name, t_lem *lem);

#endif
