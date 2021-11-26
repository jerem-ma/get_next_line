/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:57:54 by jmaia             #+#    #+#             */
/*   Updated: 2021/11/25 14:53:52 by jmaia            ###   ########.fr       */
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
	unsigned int	real_size;
}	t_file;

typedef struct s_infinite_string
{
	char			*string;
	unsigned int	i;
	unsigned int	size;
}	t_infinite_string;

char				*get_next_line(int fd);
t_file				*get_file(int fd);
char				get_next_char(t_file *file);
t_infinite_string	*init_infinite_string(void);
void				*ft_memcpy(void *dest, const void *src, size_t n);
enum e_error		append_char(t_infinite_string *str, char c);

#endif
