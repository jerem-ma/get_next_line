/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:01:52 by jmaia             #+#    #+#             */
/*   Updated: 2021/11/26 11:52:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

static char	*ft_strdup_or_null_if_empty(char *s)
{
	char	*dup;
	size_t	len_s;

	if (*s == 0)
		return (0);
	len_s = ft_strlen(s);
	dup = malloc(sizeof(*dup) * (len_s + 1));
	if (dup == 0)
		return (0);
	ft_memcpy(dup, s, sizeof(*dup) * (len_s + 1));
	return (dup);
}

static void	free_infinite_string(t_infinite_string *str)
{
	free(str->string);
	free(str);
}

static t_backpack	get_backpack(void)
{
	t_backpack	backpack;

	backpack.is_bad_backpack = 0;
	backpack.c = malloc(sizeof(*backpack.c));
	if (!backpack.c)
	{
		backpack.is_bad_backpack = 1;
		return (backpack);
	}
	backpack.line = init_infinite_string();
	if (!backpack.line)
	{
		backpack.is_bad_backpack = 1;
		free(backpack.c);
		return (backpack);
	}
	backpack.c->c = 0;
	backpack.c->is_end = 0;
	return (backpack);
}

char	*get_next_line(int fd)
{
	static t_file	file = {.i = BUFFER_SIZE, .real_size = BUFFER_SIZE,
		.is_end = 0};
	t_backpack		backpack;

	backpack = get_backpack();
	if (backpack.is_bad_backpack)
		return (0);
	file.fd = fd;
	while (backpack.c->c != '\n' && !backpack.c->is_end)
	{
		backpack.c = get_next_char(&file);
		if (backpack.c->is_end)
			continue ;
		backpack.err = append_char(backpack.line, backpack.c->c);
		if (backpack.err == e_err)
		{
			free_infinite_string(backpack.line);
			return (0);
		}
	}
	backpack.return_line = ft_strdup_or_null_if_empty(backpack.line->string);
	free_infinite_string(backpack.line);
	return (backpack.return_line);
}
