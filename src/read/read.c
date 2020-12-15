/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 22:20:06 by osalmine          #+#    #+#             */
/*   Updated: 2020/12/15 16:04:20 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem.h"

// #include <time.h>

static void str_append(char **output, char *append)
{
	char *tmp;

	tmp = ft_strjoin(append, "\n");
	ft_memdel((void**)&append);
	append = ft_strdup(tmp);
	// ft_printf("str_append, append: %p\n", append);
	ft_memdel((void**)&tmp);
	if (*output)
		tmp = ft_strjoin(*output, append);
	else
	{
		tmp = ft_strdup(append);
		// ft_printf("str_append, tmp: %p\n", tmp);
	}
	ft_memdel((void**)output);
	ft_memdel((void**)&append);
	*output = ft_strdup(tmp);
	// ft_printf("str_append, output: %p\n", output);
	ft_memdel((void**)&tmp);
}

static int	read_ant(char *line)
{
	int ants;

	ants = ft_atoi(line);
	if (!ft_isdigit((int)line[0]) || ants < 1 || ants >= INF)
		ft_exit(RED"ERROR: bad ant amount"RESET);
	return (ants);
}

void		lem_read(t_lem *lem)
{
	int		ret;
	int		i;
	int		room_type;
	char	*line;
	char	*output;

	// clock_t start = clock();
	// clock_t end;

	i = 0;
	output = NULL;
	room_type = NORMAL;
	while ((ret = get_next_line(0, &line)))
	{
		if ((int)line[0] == 0)
			ft_exit(RED"ERROR: emtpy line in map"RESET);
		if (i == 0 && (i = 1))
			lem->ant_nb = read_ant(line);
		else if (line[0] == '#')
			room_type = read_command(lem, line, room_type);
		else if ((int)line[0] != 0)
		{
			if (ft_strchr(line, ' '))
				read_room(lem, line, &room_type, i);
			else if ((i = 2))
				read_link(lem, line);
		}
		str_append(&output, line);
		// end = clock();
		// double elapsed = (double)(end - start)/CLOCKS_PER_SEC;
		// str_append(&output, ft_dtoa(elapsed, 4));
		// end = clock();
		// double elapsed = (double)(end - start)/CLOCKS_PER_SEC;

		// ft_printf("Time measeured for one read loop: %.3f seconds.\n", elapsed);
	}
	ft_printf("%s\n", output);
	free (output);
}
