/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlambert <rlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:42:41 by rlambert          #+#    #+#             */
/*   Updated: 2014/11/24 19:49:39 by rlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096
# include <stdlib.h>
# include <sys/types.h>

typedef struct	s_buf {
	char		buf[BUFF_SIZE];
	ssize_t		size;
	size_t		cursor;
}				t_buf;
int				get_next_line(int const fd, char **line);
#endif
