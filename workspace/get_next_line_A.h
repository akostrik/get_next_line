/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:00 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/29 12:13:55 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	ssize_t		b; position of the first char
//	ssize_t		e; position of the last char
//	ssize_t		nl;  position of the first newline character

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

// b
// e
// nl new line
typedef struct s_buf
{
	ssize_t			b;
	ssize_t			e;
	ssize_t			nl;
	char			*s;
	struct s_buf	*nxt;
	struct s_buf	*prv;
}	t_buf;

char	*get_next_line(int fd);
ssize_t	read_buf_and_add_to_l(int fd, t_buf **l);
char	*concat_buffers_and_update_lst(t_buf **l);
void	concat_update(t_buf **l, t_buf	*b, char *s, size_t *i_s);
void	*free_l_and_return_null(t_buf ***l);
void	print_l(t_buf **l, char *comm);

#endif
