/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlambert <rlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:43:10 by rlambert          #+#    #+#             */
/*   Updated: 2014/11/22 17:36:53 by roblabla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h" 
static ssize_t	ft_len_to_endline(int fd, t_buf *buf)
{
	if (buf->cursor >= buf->size)
	{
		buf->size = read(fd, buf->buf, BUFF_SIZE);
		buf->cursor = 0;
	}
	if (buf->size == 0)
		return (-1);
	char *endline = ft_memchr(buf->buf + buf->cursor, '\n', buf->size - buf->cursor);
	if (endline == NULL)
		return (-1);
	else
		return (endline - (buf->buf + buf->cursor));
}

static char	*ft_strnjoin(char *s1, const char *s2, size_t s2len)
{
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		new = ft_strnew(s2len);
		ft_memcpy(new, s2, s2len);
	}
	else if (s2 == NULL)
		return (s1);
	else
	{
		new = ft_strnew(ft_strlen(s1) + s2len);
		ft_strcpy(new, s1);
		ft_strncat(new, s2, s2len);
		free(s1);
	}
	return (new);
}

static char	*read_til_next_line(int fd, t_buf *buf)
{
	char	*newstr;
	ssize_t	len;

	newstr = NULL;
	while ((len = ft_len_to_endline(fd, buf)) == -1 && buf->size > 0)
	{
		newstr = ft_strnjoin(newstr, buf->buf + buf->cursor, buf->size - buf->cursor);
		buf->cursor = buf->size;
	}
	if (buf->size == 0)
		return (newstr);
	newstr = ft_strnjoin(newstr, buf->buf + buf->cursor, len);
	if (newstr == NULL)
		return (NULL);
	buf->cursor += len + 1;
	return (newstr);
}

int			get_next_line(int const fd, char **line)
{
	static t_avl	*tree;
	t_buf			*buf;
	t_avl			*cur;
	char			*tmpline;

	cur = ft_avlfind(tree, fd);
	if (cur == NULL)
	{
		buf = (t_buf*)malloc(sizeof(t_buf));
		if (buf == NULL)
			return (-1);
		buf->size = 0;
		buf->cursor = 0;
		cur = ft_avlnew(fd, NULL, 0);
		if (cur == NULL)
		{
			free(buf);
			return (-1);
		}
		cur->content = buf;
		cur->content_size = sizeof(t_buf);
		ft_avladd(&tree, cur);
	}
	else
		buf = cur->content;
	if ((tmpline = read_til_next_line(fd, buf)) == NULL)
		if (buf->size == 0)
			return (0);
		else
			return (-1);
	else
	{
		*line = tmpline;
		return (1);
	}
}
