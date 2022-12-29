/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:00 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/29 01:48:43 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	ssize_t		fst_pos; position of the first char
//	ssize_t		lst_pos; position of the last char
//	ssize_t		nl_pos;  position of the first newline character

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_buf
{
	ssize_t			p1;
	ssize_t			p2;
	ssize_t			pnl;
	char			*str;
	struct s_buf	*nxt;
	struct s_buf	*prv;
}	t_buf;

char	*get_next_line(int fd);
ssize_t	read_buf_and_add_to_l(int fd, t_buf **lst);
char	*concat_buffers_and_update_lst(t_buf ***lst);
void	concat_update(t_buf **lst, t_buf	*b, char *s, size_t *i_s);
void	free_l(t_buf **lst);
void	print_l(t_buf **l, char *comm);

#endif
