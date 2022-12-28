/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:24:00 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/28 02:01:35 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	ssize_t		fst_pos; position of the first char
//	ssize_t		lst_pos; position of the last char
//	ssize_t		nl_pos;  position of the first newline character

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_buf
{
	char					*str;
	ssize_t	fst_pos;
	ssize_t	p2;
	ssize_t	p1;
	struct s_buf	*next;
	struct s_buf	*prev;
}	t_buf;

char	*get_next_line(int fd);
void	free_lst_buf(t_buf **lst);
void	fill_buf_and_add_to_lst(t_buf	*new, t_buf **lst, ssize_t	nb_bts);
void	fill_buf_and_add_to_lst(t_buf	*new, t_buf **lst, ssize_t	nb_bts);
ssize_t	read_buf_and_add_to_lst(int fd, t_buf **lst);
void	f(t_buf **lst, t_buf	*b, char *s, ssize_t *i, size_t *i_s, t_buf *del);
char	*concat_buffers_and_update_lst(t_buf **lst);

#endif
