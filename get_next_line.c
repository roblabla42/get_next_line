/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlambert <rlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:43:10 by rlambert          #+#    #+#             */
/*   Updated: 2014/11/12 15:53:47 by rlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static ssize_t	ft_len_to_endline(int fd, t_buf *buf)
{
	if (buf->cursor >= buf->size)
	{
		buf->size = read(fd, buf->buf, BUF_SIZE);
		buf->cursor = 0;
	}
	char *endline = ft_memchr(buf->buf + buf->cursor, '\n', buf->size - buf->cursor);
	if (endline == NULL)
		return (-1);
	else
		return (endline - buf->buf + buf->cursor);
}

static char	*read_til_next_line(int fd, t_buf *buf)
{
	char	*newstr;
	ssize_t	len;

	newstr = NULL;
	while ((len = ft_len_to_endline(fd, buf)) == -1)
	{
		// TODO : Replace with own impl
		newstr = realloc(newstr, ft_strlen(newstr) + buf->size - buf->cursor + 1);
		ft_strncat(newstr, buf->buf + buf->cursor, buf->size - buf->cursor);
		buf->cursor = buf->size;
	}
	newstr = realloc(newstr, ft_strlen(newstr) + len + 1);
	if (newstr == NULL)
		return (NULL);
	ft_strncat(newstr, buf->buf + buf->cursor, len);
	buf->cursor += len;
	return (newstr);
}

int			get_next_line(int const fd, char **line)
{
	static t_avl	*tree;
	t_buf			*buf;
	t_avl			*cur;
	char			*tmpline;

	// DEBUG BLOCK
	ft_putstr("Trying to read from ");
	ft_putnbr(fd);
	ft_putendl("");
	// END DEBUG BLOCK
	cur = ft_avlfind(tree, fd);
	if (cur == NULL)
	{
		buf = (t_buf*)malloc(sizeof(t_buf));
		buf->size = 0;
		buf->cursor = 0;
		cur = ft_avlnew(fd, (void*)buf, sizeof(t_buf));
		if (cur == NULL)
			return (-1);
		ft_avladd(&tree, cur);
	}
	// DEBUG BLOCK
	ft_putstr("Got my cur : ");
	ft_putnbr((size_t)cur);
	ft_putendl("");
	// END DEBUG BLOCK
	if ((tmpline = read_til_next_line(fd, buf)) == NULL)
		return (-1);
	else
	{
		*line = tmpline;
		return (buf->size > 1 ? 1 : buf->size);
	}
}
