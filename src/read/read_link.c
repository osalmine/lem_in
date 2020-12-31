/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:23:58 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/31 14:43:01 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

static int	check_link_dups(t_lem *lem, char **links)
{
	// t_list *link_list;
	// t_link *cur_link;
	t_room *room1;
	t_room *room2;

	if (!links[0] || !links[1])
		return (1);
	// link_list = lem->link_list;
	// while (link_list)
	// {
	// 	cur_link = (t_link*)link_list->content;
	// 	if (ft_strequ(links[0], cur_link->room1->name) \
	// 		&& ft_strequ(links[1], cur_link->room2->name))
	// 		return (1);
	// 	link_list = link_list->next;
	// }
	room1 = find_hashed_room(lem, links[0]);
	room2 = find_hashed_room(lem, links[1]);
	if (find_link(room1, room2) && find_link(room2, room1))
		return (1);
	return (0);
}

static void	add_link(t_lem *lem, t_room *room, char **room_links, int i)
{
	t_link	path;
	t_list	*list;

	path.room1 = room;
	path.room2 = find_hashed_room(lem, room_links[i ? 0 : 1]);
	path.flow = INF;
	ft_lstadd(&room->links, ft_lstnew(&path, (sizeof(t_link))));
	if (!(list = (t_list *)malloc(sizeof(t_list))))
		ft_exit(RED"ERROR: malloc error"RESET);
	list->content = room->links->content;
	list->content_size = room->links->content_size;
	list->next = NULL;
	ft_lstaddlast(&lem->link_list, list);
}

void		read_link(t_lem *lem, char *line)
{
	t_room	*room;
	char	**room_links;
	int		i;
	int		duplicate;

	// t_list *lst;
	// int j = 0;
	// while (j < ((int)lem->room_count * 1.5))
	// {
	// 	lst = lem->room_hash_table[j];
	// 	ft_printf("i: %d\n", j);
	// 	while (lst)
	// 	{
	// 		ft_printf("%s\n", ((t_room*)lst->content)->name);
	// 		lst = lst->next;
	// 	}
	// 	j++;
	// }
	if (!ft_strchr(line, '-') || line[0] == '-' \
		|| line[ft_strlen(line) - 1] == '-')
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
		if (!(room = find_hashed_room(lem, room_links[i])))
			ft_exit(RED"ERROR: room not found (read_link)"RESET);
		if (room)
			add_link(lem, room, room_links, i);
		i++;
	}
	free_strsplit(&room_links);
}
