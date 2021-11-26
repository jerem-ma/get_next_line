/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:54:08 by jmaia             #+#    #+#             */
/*   Updated: 2021/11/26 11:54:51 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*get_file(int fd)
{
	t_file	*file;

	file = malloc(sizeof(*file));
	if (file == 0)
		return (0);
	file->fd = fd;
	file->i = BUFFER_SIZE;
	file->real_size = BUFFER_SIZE;
	file->is_end = 0;
	return (file);
}

t_char_file	*get_next_char(t_file	*file)
{
	t_char_file	*c_file;

	c_file = malloc(sizeof(*c_file));
	if (!c_file)
		return (0);
	if (file->is_end)
	{
		c_file->is_end = 1;
		return (c_file);
	}
	if (file->i == file->real_size)
	{
		file->real_size = read(file->fd, file->buffer, BUFFER_SIZE);
		if (file->real_size == 0 || file->real_size == -1)
			file->is_end = 1;
		else
			file->i = 0;
		return (get_next_char(file));
	}
	c_file->is_end = 0;
	c_file->c = file->buffer[file->i++];
	return (c_file);
}

t_infinite_string	*init_infinite_string(void)
{
	t_infinite_string	*str;

	str = malloc(sizeof(*str));
	if (str == 0)
		return (0);
	str->string = malloc(sizeof(*str->string) * DEFAULT_INF_STR_SIZE);
	if (str->string == 0)
	{
		free(str);
		return (0);
	}
	str->i = 0;
	str->size = DEFAULT_INF_STR_SIZE;
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_cur;
	const char	*src_cur;

	dest_cur = dest;
	src_cur = src;
	i = 0;
	while (i < n)
	{
		dest_cur[i] = src_cur[i];
		i++;
	}
	return (dest);
}

enum e_error	append_char(t_infinite_string *str, char c)
{
	char	*extended_str;
	size_t	new_size;

	if (str->i + 1 >= str->size)
	{
		new_size = str->size + DEFAULT_INF_STR_SIZE;
		extended_str = malloc(sizeof(*extended_str) * new_size);
		if (extended_str == 0)
			return (e_err);
		ft_memcpy(extended_str, str->string, str->size);
		str->size += DEFAULT_INF_STR_SIZE;
		free(str->string);
		str->string = extended_str;
		return (append_char(str, c));
	}
	str->string[str->i++] = c;
	str->string[str->i] = 0;
	return (e_ok);
}
