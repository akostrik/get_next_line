/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/02 17:53:31 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Repeated calls to get_next_line() let the text file fd, one line at a time
// Returns the line read / NULL nothing to read / NULL error
// A new line -> to return the current line
// get_next_line() reads as little as possible each time 
// File changed since the last call whereas read didn’t reach EOF -> undef. behavior
// Binary file -> undef. behavior

// Don’t read the whole file and then process each line
// YES read malloc free
// NO lseek() libft 
// get_next_line_utils.c the helper functions

// BUFFER_SIZE = 9999? 10000000?
// The buffer size and the line size can be of very different values
// The buffer size will be modified by evaluators / Moulinette
// compiler -D BUFFER_SIZE=n for read
// Cette macro définie à l’invocation du compilateur 

// ssize_t read(int fildes, void *buf, size_t nbyte)
// число реально записанных байтов от 1 до BUFFER_SIZE
// 0 EOF
// -1 ошибка

#include "get_next_line.h"

t_buf	*initialize_buf()
{
	t_buf	*buf;

	buf = (t_buf *)malloc(sizeof(t_buf));
	if (buf == NULL)
		return (NULL);
	buf -> buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buf -> buf == NULL)
		return (NULL);
	// memset('/0')
	buf -> start = 0;
	return (buf);
}

ssize_t	read_to_buf(int fd, t_buf *buf)
{
	ssize_t	nb_bytes1;
	ssize_t	nb_bytes2;

	nb_bytes1 = read(fd, &(buf->buf[buf->start]), BUFFER_SIZE - buf->start);
	if (nb_bytes1 == - 1)
		return (-1);
	if (nb_bytes1 == 0)
		return (0);
	if (nb_bytes1 < BUFFER_SIZE - buf->start)
		return (nb_bytes1);
	nb_bytes2 = read(fd, buf->buf, buf->start);
	if (nb_bytes2 == - 1)
		return (-1);
	return (nb_bytes1 + nb_bytes2);
}

char	*buf_to_str(t_buf *buf)
{
	char	*str;
	size_t	i_str;
	size_t	i_buf;

	str = (char *)malloc((BUFFER_SIZE + 1)* sizeof(char));
	if (str == NULL)
		return (NULL);
	i_str = 0;
	i_buf = buf->start;
	while (i_buf < BUFFER_SIZE)
	{
		str[i_str] = buf->buf[i_buf];
		i_str++;
		i_buf++;
	}
	i_buf = 0;
	while (i_buf < buf->start)
	{
		str[i_str] = buf->buf[i_buf];
		i_str++;
		i_buf++;
	}
	str[i_str] = '\0';
	return (str);
}


char *get_next_line(int fd)
{
	t_buf		*buf;
	ssize_t	nb_bytes;

	buf = initialize_buf();
	if (buf == NULL)
		return (NULL);
	nb_bytes = read_to_buf(fd, buf);
	if (nb_bytes == -1)
		return (NULL);
	if (nb_bytes == 0)
		return (NULL);
	// free
	return (buf_to_str(buf));
}
