/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:23:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/10/22 16:59:41 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

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

void	read_link(t_lem *lem, char *line)
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
			path->flow = INF;
			ft_lstaddlast(&room->links, ft_lstnew(path, (sizeof(t_link))));
			ft_lstaddlast(&lem->link_list, ft_lstnew(path, (sizeof(t_link))));
		}
		i++;
	}
	free_strsplit(&room_links);
}