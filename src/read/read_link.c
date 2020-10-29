/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:23:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/22 19:17:55 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static int	check_link_dups(t_lem *lem, char **links)
{
	t_room *room1;
	t_room *room2;
	t_list *link_list;
	t_link *cur_link;

    if (!links[0] || !links[1])
        return (1);
	if (!(room1 = find_room(links[0], lem)))
		ft_exit(RED"ERROR: room not found"RESET);
	if (!(room2 = find_room(links[1], lem)))
		ft_exit(RED"ERROR: room not found"RESET);
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

static void add_link(t_lem *lem, t_room *room, char **room_links, int i)
{
	t_link	*path;

    if (!(path = (t_link*)malloc(sizeof(t_link))))
        ft_exit(RED"Malloc error"RESET);
    path->room1 = ft_strdup(room->name);
    path->room2 = ft_strdup(room_links[i ? 0 : 1]);
    path->flow = INF;
    ft_lstaddlast(&room->links, ft_lstnew(path, (sizeof(t_link))));
    ft_lstaddlast(&lem->link_list, ft_lstnew(path, (sizeof(t_link))));
}

void	    read_link(t_lem *lem, char *line)
{
	t_room	*room;
	char	**room_links;
	int		i;
	int		duplicate;

	if (!ft_strchr(line, '-'))
		ft_exit(RED"ERROR: link formatting error"RESET);
	room_links = ft_strsplit(line, '-');
	i = 0;
	duplicate = check_link_dups(lem, room_links);
	while (!duplicate && room_links[i])
	{
        if (ft_strchr(line, ' '))
            ft_exit(RED"ERROR: bad input formatting"RESET);
		if (i > 1)
			ft_exit(RED"ERROR: probably too many rooms in a link"RESET);
		if (!(room = find_room(room_links[i], lem)))
			ft_exit(RED"ERROR: room not found (read_link)"RESET);
		if (room)
            add_link(lem, room, room_links, i);
		i++;
	}
	free_strsplit(&room_links);
}