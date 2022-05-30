/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:53:54 by kfujita           #+#    #+#             */
/*   Updated: 2022/05/31 02:17:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dependency:
// - malloc
// - free
#include <stdlib.h>

// dependency:
// - read
#include <unistd.h>

// dependency:
// - NULL
#include <stddef.h>

// dependency:
// - bool
// - true
// - false
#include <stdbool.h>

#include "get_next_line_bonus.h"

// 1. Get length (named `len`) up to a newline from buf
// 2. Copy&paste/concat the contents of ret&buf into the additional malloced mem
// 3. Free the original memory of ret and replace it with the newly acquired one
static bool	is_newline_picked_from_buf(t_str *buf, t_str *ret)
{
	t_str	new_ret;
	ssize_t	lf_index;
	ssize_t	i;

	lf_index = t_str_strchr(buf, '\n');
	if (lf_index >= 0)
	{
		new_ret = t_str_dup_concat(ret, buf, lf_index + 1);
		free(ret->m);
		*ret = new_ret;
		if (ret->m == NULL)
			return (true);
		i = 0;
		while ((++i + lf_index) < buf->l)
			buf->m[i - 1] = buf->m[i + lf_index];
		buf->l -= lf_index + 1;
		return (true);
	}
	new_ret = t_str_dup_concat(ret, buf, buf->l);
	free(ret->m);
	*ret = new_ret;
	if (ret->m == NULL)
		return (true);
	buf->l = 0;
	return (false);
}

// return: is successed
static t_str	*find_or_default_str(t_strarr *buf, int fd)
{
	size_t	i;
	t_str	*ret;

	i = 0;
	while (i < buf->len)
	{
		if (buf->elems[i].fd == fd)
			return (&(buf->elems[i]));
		i++;
	}
	ret = append_to_strarr(buf);
	if (ret != NULL)
	{
		*ret = g_STR_BUF;
		ret->fd = fd;
		ret->m = malloc(ret->cap);
		if (ret->m == NULL)
		{
			remove_str(buf, fd);
			ret = NULL;
		}
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_strarr	bufarr = {NULL, 0, 0};
	t_str			*buf;
	t_str			ret;

	ret = g_STR_ZERO;
	buf = find_or_default_str(&bufarr, fd);
	if (buf == NULL)
		return (NULL);
	if (buf->l > 0 && is_newline_picked_from_buf(buf, &ret))
		return (ret.m);
	while (true)
	{
		buf->l = read(fd, buf->m, buf->cap);
		if (buf->l <= 0)
		{
			free(buf->m);
			remove_str(&bufarr, fd);
			break ;
		}
		if (is_newline_picked_from_buf(buf, &ret) == true)
			break ;
	}
	return (ret.m);
}
