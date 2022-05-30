/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:53:46 by kfujita           #+#    #+#             */
/*   Updated: 2022/05/31 01:54:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
	int		fd;
}	t_str;

typedef struct s_strarr {
	t_str	*elems;
	size_t	len;
	size_t	cap;
}	t_strarr;

static const t_str		g_STR_ZERO = {NULL, 0, 0, 0};
static const t_str		g_STR_BUF = {NULL, 0, BUFFER_SIZE, 0};

static const t_strarr	g_STRARR_ZERO = {NULL, 0, 0};

char	*get_next_line(int fd);

ssize_t	t_str_strchr(const t_str *str, char c);
t_str	t_str_dup_concat(const t_str *base, const t_str *back, ssize_t backlen);

t_str	*append_to_strarr(t_strarr *target);
void	remove_str(t_strarr *target, int fd);

#endif
