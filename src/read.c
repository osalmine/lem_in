/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2020/08/26 12:16:31 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int	read_command(t_lem *lem, char *line, int room_type)
{
	t_list *rooms;

	if (ft_strequ(line, "##start"))
	{
		rooms = lem->room_list;
		while (rooms)
		{
			if (((t_room*)rooms->content)->type == START)
				ft_exit(RED"ERROR: multiple start rooms"RESET);
			rooms = rooms->next;
		}
		return (START);
	}
	else if (ft_strequ(line, "##end"))
	{
		rooms = lem->room_list;
		while (rooms)
		{
			if (((t_room*)rooms->content)->type == END)
				ft_exit(RED"ERROR: multiple end rooms"RESET);
			rooms = rooms->next;
		}
		return (END);
	}
	return (room_type);
}

static void	read_room(t_lem *lem, char *line, int *room_type)
{
	char	**room_arr;
	int		arr_len;
	t_room	*room;

	room_arr = ft_strsplit(line, ' ');
	arr_len = 0;
	while (room_arr[arr_len])
		arr_len++;
	if (arr_len != 3 || room_arr[0][0] == 'L')
		ft_exit(RED"ERROR: room error"RESET);
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		ft_exit(RED"Malloc error"RESET);
	room->name = ft_strdup(room_arr[0]);
	room->x = ft_atoi(room_arr[1]);
	room->y = ft_atoi(room_arr[2]);
	room->visited = FALSE;
	if (*room_type == START)
		room->has_ant = lem->ant_nb;
	else
		room->has_ant = FALSE;
	room->type = *room_type;
	room->links = NULL;
	*room_type = NORMAL;
	free_strsplit(&room_arr);
	ft_lstaddlast(&lem->room_list, ft_lstnew(room, sizeof(t_room)));
}

static int	check_link_dups(t_lem *lem, char **links)
{
	t_room *room1;
	t_room *room2;
	t_list *link_list;
	t_link *cur_link;

	if (!(room1 = find_room(links[0], lem)))
		ft_exit(RED"ERROR: room1 not found (check_link_dups)"RESET);
	if (!(room2 = find_room(links[1], lem)))
		ft_exit(RED"ERROR: room2 not found (check_link_dups)"RESET);
	link_list = lem->link_list;
	while (link_list)
	{
		cur_link = (t_link*)link_list->content;
		if (ft_strequ(links[0], cur_link->room1) && ft_strequ(links[1], cur_link->room2))
			return (1);
		link_list = link_list->next;
	}
	return (0);
}

static void	read_link(t_lem *lem, char *line)
{
	t_room	*room;
	t_link	*path;
	char	**room_links;
	int		i;
	int		duplicate;

	room_links = ft_strsplit(line, '-');
	i = 0;
	duplicate = check_link_dups(lem, room_links);
	while (!duplicate && room_links[i])
	{
		if (i > 1)
			ft_exit(RED"ERROR: probably too many rooms in a link"RESET);
		if (!(room = find_room(room_links[i], lem)))
			ft_exit(RED"ERROR: room not found (read_link)"RESET);
		if (room)
		{
			if (!(path = (t_link*)malloc(sizeof(t_link))))
				ft_exit(RED"Malloc error"RESET);
			path->room1 = ft_strdup(room->name);
			path->room2 = ft_strdup(room_links[i ? 0 : 1]);
			ft_lstaddlast(&room->links, ft_lstnew(path, (sizeof(t_link))));
			ft_lstaddlast(&lem->link_list, ft_lstnew(path, (sizeof(t_link))));
		}
		i++;
	}
	free_strsplit(&room_links);
}

static char	*str_append(char *str, char *append)
{
	char *tmp;

	tmp = ft_strjoin(append, "\n");
	ft_memdel((void**)&append);
	append = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	if (str)
		tmp = ft_strjoin(str, append);
	else
		tmp = ft_strdup(append);
	ft_memdel((void**)&str);
	ft_memdel((void**)&append);
	str = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	return (str);
}

void		lem_read(t_lem *lem)
{
	int		ret;
	int		i;
	int		room_type;
	char	*line;
	char	*output;

	i = 1;
	output = NULL;
	room_type = NORMAL;
	while ((ret = get_next_line(0, &line)))
	{
		if (ft_isdigit(line[0]) && i == 1 && !(i = 0))
			lem->ant_nb = ft_atoi(line);
		else if (line[0] == '#')
			room_type = read_command(lem, line, room_type);
		else
		{
			if (ft_strchr(line, ' '))
				read_room(lem, line, &room_type);
			else
				read_link(lem, line);
		}
		output = str_append(output, line);
	}
	ft_printf("%s\n", output);
}
