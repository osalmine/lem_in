/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2020/06/20 23:52:16 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int	read_command(char *line, int room_type)
{
	if (ft_strequ(line, "##start"))
		return (START);
	else if (ft_strequ(line, "##end"))
		return (END);
	return (room_type);
}

static void	read_room(t_lem *lem, char *line, int room_type)
{
	char	**room_arr;
	int		arr_len;
	t_room	*room;

	room_arr = ft_strsplit(line, ' ');
	arr_len = 0;
	while (room_arr[arr_len])
		arr_len++;
	if (arr_len != 3 || room_arr[0][0] == 'L')
		ft_exit("ERROR\n");
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		ft_exit("Malloc error\n");
	room->name = ft_strdup(room_arr[0]);
	room->x = ft_atoi(room_arr[1]);
	room->y = ft_atoi(room_arr[2]);
	room->visited = FALSE;
	room->has_ant = FALSE;
	room->type = room_type;
	room->paths = NULL;
	free_strsplit(&room_arr);
	ft_lstadd(&lem->room_list, ft_lstnew(room, (sizeof(room) + sizeof(t_path) + 20)));
}

static void read_link(t_lem *lem, char *line)
{
	t_room	*room;
	t_path	*path;
	char	**room_links;
	int		i;

	room_links = ft_strsplit(line, '-');
	ft_printf("Room links: %la\n", room_links);
	ft_printf("Line in read link: %s\n", line);
	i = 0;
	while (room_links[i])
	{
		room = find_room(room_links[i], lem);
		if (room)
		{
			if (!room->paths)
			{
				ft_printf("No paths for room %s\n", room->name);
				if (!(room->paths = (t_list*)malloc(sizeof(t_list))))
					ft_exit("Malloc error\n");
			}
			if (!(path = (t_path*)malloc(sizeof(t_path))))
				ft_exit("Malloc error\n");
			path->room1 = ft_strdup(room->name);
			ft_printf("room_links[%i]: %s\n", i, room_links[i]);
			path->room2 = ft_strdup(room_links[i]);
			ft_printf("path->room2: %s\n", path->room2);
			ft_lstadd(&room->paths, ft_lstnew(path, (sizeof(path))));
			// free(room->name);
			// room->name = ft_strdup("5");
		}
		i++;
	}
	free_strsplit(&room_links);
}

void		lem_read(t_lem *lem)
{
	int		ret;
	int		i;
	int		room_type;
	char	*line;

	i = 0;
	room_type = NORMAL;
	while ((ret = get_next_line(0, &line)) && ++i)
	{
		if (i == 1)
			lem->ant_nb = ft_atoi(line);
		else if (line[0] == '#')
			room_type = read_command(line, room_type);
		else
		{
			if (ft_strchr(line, ' '))
			{
				read_room(lem, line, room_type);
				room_type = NORMAL;
			}
			else
				read_link(lem, line);
		}
		ft_printf("%s\n", line);
		free(line);
	}
	ft_printf("number of ants: %d\n", lem->ant_nb);
	while (lem->room_list->next)
	{
		t_room *new_room;
		t_path *path;
		new_room = (t_room*)lem->room_list->content;
		ft_printf("Room name: %s, room type: %d, x: %d, y: %d, visited: %d, has_ant: %d\n", new_room->name, new_room->type, new_room->x, new_room->y, new_room->visited, new_room->has_ant);
		while (new_room->paths->next)
		{
			path = (t_path*)new_room->paths->content;
			ft_printf("Path room1: %s, room2: %s\n", path->room1, path->room2);
			new_room->paths = new_room->paths->next;
		}
		lem->room_list = lem->room_list->next;
	}
}
