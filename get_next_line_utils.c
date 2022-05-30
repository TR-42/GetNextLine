/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:53:36 by kfujita           #+#    #+#             */
/*   Updated: 2022/05/31 00:50:10 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dependency:
// - NULL
#include <stddef.h>

// dependency:
// - malloc
// - free
#include <stdlib.h>

#include "get_next_line.h"

ssize_t	t_str_strchr(const t_str *str, char c)
{
	ssize_t	i;

	if (str == NULL || str->m == NULL || str->l <= 0)
		return (-1);
	i = 0;
	while (i < str->l && str->m[i] != c)
		i++;
	if (i == str->l)
		return (-1);
	else
		return (i);
}

t_str	t_str_dup_concat(const t_str *front, const t_str *back, ssize_t backlen)
{
	t_str	ret;

	ret = g_STR_ZERO;
	ret.m = malloc(front->l + backlen + 1);
	if (ret.m == NULL)
		return (ret);
	while (ret.l < front->l)
	{
		ret.m[ret.l] = front->m[ret.l];
		ret.l++;
	}
	while ((ret.l - front->l) < backlen)
	{
		ret.m[ret.l] = back->m[ret.l - front->l];
		ret.l++;
	}
	ret.m[ret.l] = '\0';
	return (ret);
}
