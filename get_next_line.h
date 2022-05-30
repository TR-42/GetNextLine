/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:53:01 by kfujita           #+#    #+#             */
/*   Updated: 2022/05/31 00:49:44 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// dependency:
// - ssize_t
# include <sys/types.h>

// dependency:
// - NULL
# include <stddef.h>

typedef struct s_str {
	char	*m;
	ssize_t	l;
	ssize_t	cap;
}	t_str;

static const t_str	g_STR_ZERO = {NULL, 0, 0};
static const t_str	g_STR_BUF = {NULL, 0, BUFFER_SIZE};

char	*get_next_line(int fd);

ssize_t	t_str_strchr(const t_str *str, char c);
t_str	t_str_dup_concat(const t_str *base, const t_str *back, ssize_t backlen);

#endif
