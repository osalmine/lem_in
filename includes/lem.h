/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 19:01:54 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 14:54:03 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_H

# define LEM_H

# include "../libft/libft.h"

# ifndef TRUE_FALSE
#  define TRUE_FALSE

#  define TRUE	1
#  define FALSE	0

# endif

# ifndef BUFF
#  define BUFF

#  define BUFF_SIZE 1000

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
**	visited_ek:	if the room has been visited by path search
**	x:			x-coordiante
**	y:			y-coordinate
**	has_ant:	TRUE (=1) if room has ant, else FALSE (=0)
**	type:		room's type. START (=1) if room is starting room,
**				END (=2) if room is goal room, else NORMAL (=0)
**	in_path:	TRUE if room is in a path, else FALSE
**	links:		list of connections to the room
*/

typedef struct	s_room
{
	char	*name;
	int		id;
	int		visited;
	int		visited_ek;
	int		x;
	int		y;
	int		has_ant;
	int		type;
	int		in_path;
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
**	path_arr:	rooms on the path in order
**	len:		path's length
**	colour:		the colour of the path (debugging and prettiness)
*/

typedef struct	s_path
{
	t_room	**path_arr;
	int		len;
	char	*colour;
}				t_path;

/*
**	Struct for each ant
**	id:			ant's id
**	room:		ant's current room
**	path:		ant's path
**	move_nb:	how many times has the ant moved
**				(to keep track where it is relative to the path)
*/

typedef struct	s_ant
{
	int		id;
	t_room	*room;
	t_path	*path;
	int		move_nb;
}				t_ant;

/*
**	Set of paths
**	cost:	cost of the set
**	len:	combined lenght of the paths
**	flow:	flow of the set
**	paths:	all the paths in the set
*/

typedef struct	s_set
{
	int		cost;
	int		len;
	int		flow;
	t_list	*paths;
}				t_set;

/*
**	t_lem is the main struct
**	ant_nb:			total ant amount
**	ants:			list of all ants
**	room_list:		list of all rooms
**	link_list:		list of all the links
**	best_set:		the best set
**	ek_set:			the current round's set
**	opts:			options struct
**	moves_count:	counts the number of turns (lines)
**	start:			start room
**	end:			end room
**	max_flow:		maximum flow of the graph used in assigning ants
**	room_count:		how many rooms is there
**	path_amount:	amount of paths found by bfs
**	room_arr:		array of the rooms for a faster search with an index
**	room_links_arr:	array of links to rooms: -1 if no link,
**					else the number is the index in room_arr
**					that the room connects to
**	room_hash_table:list of lists to rooms in hashed indexes
*/

typedef struct	s_lem
{
	int		ant_nb;
	t_list	*ants;
	t_list	*room_list;
	t_list	*link_list;
	t_set	*best_set;
	t_set	*ek_set;
	t_opts	opts;
	int		moves_count;
	t_room	*start;
	t_room	*end;
	int		max_flow;
	int		room_count;
	int		path_amount;
	t_room	**room_arr;
	int		**room_links_arr;
	t_list	**room_hash_table;
}				t_lem;

/*
**	Init and read functions
*/

t_lem			*lem_init(int ac, char **av);
void			lem_flags(t_lem *lem, int ac, char **av);
void			lem_read(t_lem *lem);
void			init_ants(t_lem *lem);
void			read_link(t_lem *lem, char *line);
void			read_room(t_lem *lem, char *line, \
					int *room_type, int format_check);
int				read_command(t_lem *lem, char *line);
void			create_room_table(t_lem *lem);
void			create_link_table(t_lem *lem);
t_set			*init_set(void);

/*
**	Finding functions
*/

t_room			*find_hashed_room(t_lem *lem, char *name);
t_room			*find_room_by_type(int type, t_lem *lem);
int				find_from_que(t_room **que, t_room *room);
int				find_in_path(t_list *list, t_room *room, t_room *end);
t_link			*find_link(t_room *room1, t_room *room2);
t_path			*find_path(t_list *list, t_room *room, t_room *end);

/*
**	Algo functions
*/

void			guide_ants(t_lem *lem);
void			find_paths(t_lem *lem);
void			assign_paths(t_lem *lem);
t_room			**bfs(t_lem *lem);
void			flows_pathfinder(t_lem *lem);
void			turn_loop(t_lem *lem);

/*
**	Print and debug functions
*/

void			print_paths(t_lem *lem, t_list *lem_paths);
void			debug_out(t_lem *lem);

/*
**	Free functions
*/

void			free_strsplit(char ***str);
void			free_set(t_set **set);

/*
**	Utility functions
*/

t_room			**create_room_arr(t_lem *lem);
void			push_to_room_arr(t_room **arr, t_room *room);
t_room			**room_arr_reverse(t_room **arr);
int				arr_size(char **arr);
int				room_arr_size(t_room **arr);
void			sort_paths(t_list *paths);
void			add_path(t_lem *lem, t_room **path, \
					t_list **path_list, t_set **set);
void			assign_flows(t_room **path);
void			reset_rooms_bfs(t_lem *lem);
void			reset_rooms_ek(t_lem *lem);
int				min_3(int x, int y, int z);
int				max_flow(t_lem *lem);
int				*get_steps(t_lem *lem, int *total);
int				*calc_div(t_lem *lem, int *divide, int total, int *steps);
int				find_longest(int *division, int *steps, int max);
int				*split_remainder(int *ant_division, int remainder, \
					t_lem *lem, int **longest);
void			paths_to_ants(t_lem *lem, int *division, int max);
unsigned int	hash(char *str, int size);
int				get_max(t_lem *lem, t_list *lst);
void			str_append(char **lines, char *append);
int				get_number(char *line);

#endif
