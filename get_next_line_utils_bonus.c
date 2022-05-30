/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:53:38 by kfujita           #+#    #+#             */
/*   Updated: 2022/05/31 02:17:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dependency:
// - NULL
#include <stddef.h>

// dependency:
// - malloc
// - free
#include <stdlib.h>

#include <stdbool.h>

#include "get_next_line_bonus.h"

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

t_str	*append_to_strarr(t_strarr *target)
{
	t_str	*newarr;
	size_t	i;

	if (target->cap <= target->len)
	{
		target->cap++;
		newarr = malloc(target->cap * sizeof(t_str));
		if (newarr == NULL)
			return (NULL);
		i = 0;
		while (i < target->len)
		{
			newarr[i] = target->elems[i];
			i++;
		}
		free(target->elems);
		target->elems = newarr;
	}
	target->len++;
	return (target->elems + target->len - 1);
}

void	remove_str(t_strarr *target, int fd)
{
	size_t		i;

	i = 0;
	while (i < target->len && target->elems[i].fd != fd)
		i++;
	if (i == target->len)
		return ;
	if (target->len == 1)
	{
		free(target->elems);
		*target = g_STRARR_ZERO;
		return ;
	}
	target->len--;
	target->elems[i] = target->elems[target->len];
}
