/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:54 by osalmine          #+#    #+#             */
/*   Updated: 2020/11/04 20:07:26 by osalmine         ###   ########.fr       */
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
# define INF	2147483647

/*
**	Struct for options
**	All default to FALSE (= 0)
**	debug:		see debug information about structures
**	lines:		outputs the number of turns used (lines outputted)
**	paths:		outputs the paths that were found
**	colours:	if set to TRUE, paths are coloured
*/

typedef struct	s_options
{
	int	debug;
	int lines;
	int paths;
	int colours;
}				t_opts;

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
**	weight:		distance from starting node
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
	int		weight;
	t_list	*links;
}				t_room;

/*
**	Struct to see where the room is connected to
**	room1:	first door
**	room2:	second door
**	flow:	link's current flow (initialized as INF)
*/

typedef struct	s_link
{
	t_room	*room1;
	t_room	*room2;
	int		flow;
}				t_link;

/*
**	Struct for each path
**	path_arr:	names of the rooms on the path in order
**	len:		path's lenght
**	colour:		the colour of the path (debugging and prettiness)
**	in_use:		if the path can be used
*/

typedef struct	s_path
{
	t_room	**path_arr;
	int		len;
	char	*colour;
	int		in_use;
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
**	ant_nb:			total ant amount
**	ants:			list of all ants
**	room_list:		list of all rooms
**	link_list:		list of all the links
**	paths_list:		list of all the paths
**	opts:			options struct
**	paths_bef_ek:	paths before running them through edmonds-karp pathfinding
**	moves_count:	counts the number of turns (lines)
**	start:			start room
**	end:			end room
**	max_flow:		maximum flow of the graph
*/

typedef struct	s_lem
{
	int		ant_nb;
	int		room_nb;
	t_list	*ants;
	t_list	*room_list;
	t_list	*link_list;
	t_list	*paths_list;
	t_opts	*opts;
	t_list	*paths_bef_ek;
	int		moves_count;
	t_room	*start;
	t_room	*end;
	int		max_flow;
	t_room	***room_table;
}				t_lem;

/*
**	Init and read functions
*/

t_lem	*lem_init(int ac, char **av);
void	lem_flags(t_lem *lem, int ac, char **av);
void	lem_read(t_lem *lem);
void	init_ants(t_lem *lem);
void	read_link(t_lem *lem, char *line);
void	read_room(t_lem *lem, char *line, int *room_type, int format_check);
int		read_command(t_lem *lem, char *line, int room_type);
// void	remove_dead_ends(t_lem *lem);
void	create_room_table(t_lem *lem);

/*
**	Finding functions
*/

t_room	*find_room(char *name, t_lem *lem);
t_room  *find_room_by_type(int type, t_lem *lem);
int     find_from_que(t_room **que, t_room *room);
int		find_in_path(t_list *list, t_room *room, t_room *end);
t_link	*find_link(t_lem *lem, char *room1, char *room2);
t_path  *find_path(t_list *list, t_room *room, t_room *end);

/*
**	Pathfinding functions
*/

void	guide_ants(t_lem *lem);
void    find_paths(t_lem *lem);
void    assign_paths(t_lem *lem);
t_room	**bfs(t_lem *lem);
void	flows_pathfinder(t_lem *lem);

/*
**	Print and debug functions
*/

void    print_paths(t_lem *lem);

/*
**	Free functions
*/

void	free_lem(t_lem *lem);
void	free_strsplit(char ***str);
// void	free_path(void *path, size_t size);
void	free_a_path(t_path **path, size_t size);
void	free_room(void *room, size_t size);
void	free_link(void *link, size_t size);

/*
**	Utility functions
*/

int 	room_count(t_lem* lem);
char	**create_arr(t_lem *lem, ssize_t size);
t_room	**create_room_arr(t_lem *lem, ssize_t size);
void	push_to_arr(char **que, char *room);
void	push_to_room_arr(t_room **arr, t_room *room);
char	**arr_reverse(char **arr);
t_room	**room_arr_reverse(t_room **arr);
int		arr_size(char **arr);
int		room_arr_size(t_room **arr);
void	sort_paths(t_lem *lem);
char	**ft_2dstrdup(char **str);
void	add_path(t_lem *lem, t_room **path, t_list **path_list);
int     check_for_dup_path_size_1(t_lem *lem, t_room **path);
int     check_for_dup_path(t_list *paths_lst, t_room **path);
void	assign_weights(t_lem *lem, t_room **path);
void	assign_flows(t_lem *lem, t_room **path);
void	reset_rooms(t_lem *lem);
int		min_3(int x, int y, int z);
int		max_flow(t_lem *lem);

#endif
