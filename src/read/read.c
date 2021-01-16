/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/14 12:09:34 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

#include <time.h>


static void	str_append(char **lines, char *append)
{
	char *tmp;

	// if (*lines)
	// 	tmp = ft_strjoin(*lines, append);
	// else
	// 	tmp = ft_strdup(append);
	tmp = ft_strjoin(*lines, append);
	ft_memdel((void**)lines);
	// ft_memdel((void**)&append);
	*lines = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
}

// static void		check_room_dups(t_lem *lem)
// {
// 	t_list *rooms;
// 	t_list *room;

// 	rooms = lem->room_list;
// 	while (rooms)
// 	{
// 		room = rooms;
// 		while (room)
// 		{
// 			if (((t_room*)room->content)->x == ft_atoi(room_arr[1]) && \
// 				((t_room*)room->content)->y == ft_atoi(room_arr[2]))
// 				ft_exit(RED"ERROR: duplicated coordinates"RESET);
// 			if (ft_strequ(((t_room*)room->content)->name, room_arr[0]))
// 				ft_exit(RED"ERROR: duplicated room name"RESET);
// 			room = room->next;
// 		}
// 		rooms = rooms->next;
// 	}
// }

static int	read_ant(char *line)
{
	int ants;

	ants = ft_atoi(line);
	if (!ft_isdigit((int)line[0]) || ants < 1 || ants >= INF)
		ft_exit(RED"ERROR: bad ant amount"RESET);
	return (ants);
}

static t_list	**create_hash_list(t_lem *lem)
{
	t_list	**room_hash_table;
	int		i;

	if (!(room_hash_table = (t_list**)malloc(sizeof(t_list*) * ((int)lem->room_count * 1.5))))
		ft_exit("ERROR: create_hash_list malloc error");
	i = 0;
	while (i < ((int)lem->room_count * 1.5))
		room_hash_table[i++] = NULL;
	return (room_hash_table);
}

static void	read_input(t_lem *lem, char *lines)
{
	char	**input;
	int		j;
	int		jj;
	int		i;
	int		room_type;
	
	i = 0;
	room_type = NORMAL;
	input = ft_strsplit(lines, '\n');
	j = 0;
	lem->room_count = 0;
	// clock_t begin;
	// clock_t end;
	// double time;
	// begin = clock();
	while (input[j])
	{
		if ((int)input[j][0] == 0)
			ft_exit(RED"ERROR: emtpy line in map"RESET);
		else if (i == 0 && (i = 1) && (jj = j + 1))
			lem->ant_nb = read_ant(input[j]);
		else if (ft_strchr(input[j], ' '))
			lem->room_count++;
		else if (input[j][0] != '#')
			break ;
		j++;
	}
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf(RED"READ INPUT 1 TIME: %lf\n"RESET, time);
	// ft_printf("Room count: %d\n", lem->room_count);
	lem->room_hash_table = create_hash_list(lem);
	// begin = clock();
	j = jj;
	while (input[j])
	{
		if (input[j][0] == '#')
			room_type = read_command(lem, input[j]);
		else if ((int)input[j][0] != 0)
		{
			if (ft_strchr(input[j], ' '))
				read_room(lem, input[j], &room_type, i);
			else if ((i = 2))
				read_link(lem, input[j]);
		}
		j++;
	}
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf(RED"READ INPUT 2 TIME: %lf\n"RESET, time);
	free_strsplit(&input);
}

void		lem_read(t_lem *lem)
{
	int		ret;
	char	line[BUFF_SIZE + 1];
	char	*lines;
	char	*tmp;

	// clock_t begin;
	// clock_t end;
	// double time;
	lines = NULL;
	tmp = NULL;
	// begin = clock();
	while ((ret = read(0, line, BUFF_SIZE)))
	{
		line[ret] = '\0';
		str_append(&lines, line);
	}
	// ft_putstr(lines);
	if (ret < 0)
		ft_exit("ERROR: read error");
	if (!lines)
		ft_exit(RED"ERROR: No input"RESET);
	if (lines[ft_strlen(lines) - 1] != '\n')
	{
		tmp = ft_strjoin(lines, "\n");
		ft_strdel(&lines);
		lines = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf(RED"INPUT READ TIME: %lf\n"RESET, time);
	// begin = clock();
	read_input(lem, lines);
	// check_room_dups(lem);
	// end = clock();
	// time = (double)(end - begin) / CLOCKS_PER_SEC;
	// while (1);

	// ft_printf("%s\n", lines);
	ft_putendl(lines);

	// ft_printf(RED"INPUT PROCESS TIME: %lf\n"RESET, time);
	// free(lines);
	ft_strdel(&lines);
	// while (1);
}
