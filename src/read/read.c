/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/22 16:24:16 by osalmine         ###   ########.fr       */
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
	room->weight = INF - 1;
	*room_type = NORMAL;
	free_strsplit(&room_arr);
	ft_lstaddlast(&lem->room_list, ft_lstnew(room, sizeof(t_room)));
}

static void str_append(char **output, char *append)
{
	char *tmp;

	tmp = ft_strjoin(append, "\n");
	ft_memdel((void**)&append);
	append = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	if (*output)
		tmp = ft_strjoin(*output, append);
	else
		tmp = ft_strdup(append);
	ft_memdel((void**)output);
	ft_memdel((void**)&append);
	*output = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
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
		str_append(&output, line);
	}
	ft_printf("%s\n", output);
}
