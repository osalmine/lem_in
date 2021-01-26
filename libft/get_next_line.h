/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:30:58 by osalmine          #+#    #+#             */
/*   Updated: 2021/01/26 14:01:02 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define FD_MAX 4620

# ifndef BUFF
#  define BUFF

#  define BUFF_SIZE 1000

# endif

int	get_next_line(const int fd, char **line);

#endif
