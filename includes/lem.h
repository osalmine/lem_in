/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/09/07 14:34:10 by osalmine         ###   ########.fr       */
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
**	debug:	set to TRUE (=1) for debugging
**	lines:	program outputs the number of turns used (lines outputted)
**	paths:	output the paths
*/

typedef struct	s_options
{
	int	debug;
	int lines;
	int paths;
	int colours;
}				t_opts;

/*
**	Struct to see where the room is connected to
**	room1:	first door
**	room2:	second door
**	flow:	links current flow (initialized as 0)
*/

typedef struct	s_link
{
	char	*room1;
	char	*room2;
	int		flow;
}				t_link;

/*
**	Struct for each room
**	name:		room's name
**	id:			unique number id
**	visited:	if the room has been visited by the search algo that turn
**	x:			x-coordiante
**	y:			y-coordinate
**	has_ant:	TRUE (=1) if room has ant, else FALSE (=0)
**	type:		room's type. START (=1) if room is starting room,
**				END (=2) if room is goal room, else NORMAL (=0)
**	path:		list of connections to the room
*/

typedef struct	s_room
{
	char	*name;
	int		id;
	int		visited;
	int		x;
	int		y;
	int		has_ant;
	int		type;
	t_list	*links;
}				t_room;

/*
**	Struct for each path
**	path:	
*/

typedef struct	s_path
{
	char	**path_arr;
	int		len;
	char	*colour;
}				t_path;

/*
**	Struct for each ant
**	id:			ant's id
**	has_moved:	TRUE (=1) if ant has moved that turn, else FALSE (=0)
**	room:		ant's current room
**	path:		ant's path
**	move_nb:	how many times has the ant moved (to keep track where it is relative to the path)
*/

typedef struct	s_ant
{
	int		id;
	int		has_moved;
	t_room	*room;
	t_path	*path;
	int		move_nb;
}				t_ant;

/*
**	t_lem is the main struct
**	ant_nb:		total ant amount
**	ants:		list of all ants
**	room_list:	list of all rooms
**	link_list:	list of all the links
**	paths_list:	list of all the paths
**	opts:		options struct
*/

typedef struct	s_lem
{
	int		ant_nb;
	t_list	*ants;
	t_list	*room_list;
	t_list	*link_list;
	t_list	*paths_list;
	t_opts	*opts;
	int		moves_count;
}				t_lem;

/*
**	Init and read functions
*/

t_lem	*lem_init(int ac, char **av);
void	lem_flags(t_lem *lem, int ac, char **av);
void	lem_read(t_lem *lem);
void	init_ants(t_lem *lem);

/*
**	Finding functions
*/

t_room	*find_room(char *name, t_lem *lem);
t_room  *find_room_by_type(int type, t_lem *lem);
int     find_from_que(char **que, char *name);
int		find_in_path(t_lem *lem, t_room *room, t_room *end);

/*
**	Pathfinding functions
*/

void	guide_ants(t_lem *lem);
void    find_paths(t_lem *lem, t_room *start, t_room *end);
void    assign_paths(t_lem *lem, t_room *start);

/*
**	Print and debug functions
*/

void    print_paths(t_lem *lem);

/*
**	Free functions
*/

void	free_lem(t_lem *lem);
void	free_room_arr(char ***str, int len);
void	free_strsplit(char ***str);

/*
**	Utility functions
*/

int 	room_count(t_lem* lem);
char	**create_arr(t_lem *lem, ssize_t size);
void	push_to_arr(char **que, char *room);
char	**arr_reverse(char **arr);
int		arr_size(char **arr);

#endif
