/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:57:54 by jmaia             #+#    #+#             */
/*   Updated: 2021/11/26 11:30:11 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define DEFAULT_INF_STR_SIZE 50

enum e_error { e_ok, e_err };

typedef struct s_file
{
	int				fd;
	unsigned int	i;
	char			buffer[BUFFER_SIZE];
	ssize_t			real_size;
	int				is_end;
}	t_file;

typedef struct s_infinite_string
{
	char			*string;
	unsigned int	i;
	unsigned int	size;
}	t_infinite_string;

typedef struct s_char_file
{
	char	c;
	int		is_end;
}	t_char_file;

typedef struct s_backpack
{
	t_infinite_string	*line;
	char				*return_line;
	t_char_file			*c;
	enum e_error		err;
	int					is_bad_backpack;
}	t_backpack;

char				*get_next_line(int fd);
t_file				*get_file(int fd);
t_char_file			*get_next_char(t_file *file);
t_infinite_string	*init_infinite_string(void);
void				*ft_memcpy(void *dest, const void *src, size_t n);
enum e_error		append_char(t_infinite_string *str, char c);

#endif
