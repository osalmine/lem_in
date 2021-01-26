/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 13:49:42 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

static int		read_ant(char *line)
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

	if (!(room_hash_table = (t_list**)malloc(sizeof(t_list*) \
			* ((int)lem->room_count * 1.5))))
		ft_exit("ERROR: create_hash_list malloc error");
	i = 0;
	while (i < ((int)lem->room_count * 1.5))
		room_hash_table[i++] = NULL;
	return (room_hash_table);
}

static int		get_room_amount(t_lem *lem, char **input, int *i)
{
	int index;
	int j;

	j = 0;
	lem->room_count = 0;
	while (input[j])
	{
		if (*i == 0 && (*i = 1))
		{
			lem->ant_nb = read_ant(input[j]);
			index = j + 1;
		}
		else if (ft_strchr(input[j], ' '))
			lem->room_count++;
		else if (input[j][0] != '#')
			break ;
		j++;
	}
	lem->room_hash_table = create_hash_list(lem);
	return (index);
}

static void		read_input(t_lem *lem, char *lines)
{
	char	**input;
	int		j;
	int		i;
	int		room_type;

	i = 0;
	room_type = NORMAL;
	input = ft_strsplit(lines, '\n');
	if (ft_strstr(lines, "\n\n"))
		ft_exit(RED"ERROR: emtpy line in map"RESET);
	j = get_room_amount(lem, input, &i);
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
	free_strsplit(&input);
}

void			lem_read(t_lem *lem)
{
	int		ret;
	char	line[BUFF_SIZE + 1];
	char	*lines;
	char	*tmp;

	lines = NULL;
	tmp = NULL;
	while ((ret = read(0, line, BUFF_SIZE)) > 0)
	{
		line[ret] = '\0';
		str_append(&lines, line);
	}
	if (ret < 0 || !lines)
		ft_exit("ERROR: read error");
	if (lines[ft_strlen(lines) - 1] != '\n')
	{
		tmp = ft_strjoin(lines, "\n");
		ft_strdel(&lines);
		lines = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	read_input(lem, lines);
	ft_putendl(lines);
	ft_strdel(&lines);
}
