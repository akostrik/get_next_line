/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/05 15:20:20 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Repeated calls to get_next_line() let the text file fd, one line at a time
// Returns the line read / NULL nothing to read / NULL error
// A new line -> return the current line
// get_next_line() reads as little as possible each time 
// YES read malloc free
// NO  lseek() libft 

// ssize_t read(int fildes, void *buf, size_t nbyte)
// число реально записанных байтов [1 .. BUFFER_SIZE], 0 EOF, -1 ошибка

// compiler -D BUFFER_SIZE=n, macro définie à l’invocation du compilateur
// BUFFER_SIZE = 9999? 10000000?
// BUFFER_SIZE and the line size - very different values
// BUFFER_SIZE modified by evaluators / Moulinette

// get_next_line_utils.c the helper functions
// File changed since the last call whereas read didn’t reach EOF -> undef. behavior
// Binary file -> undef. behavior
// Don’t read the whole file and then process each line

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
	buf->end_old_content = 0;
	buf->start_old_content = 0;
	return (buf);
}

ssize_t	read_to_buf(int fd, t_buf *buf)
{
	ssize_t	nb_bytes;

	nb_bytes = read(fd, buf->buf, BUFFER_SIZE);
	if (nb_bytes == - 1)
		return (-1);
	if (nb_bytes == 0)
		return (0);
	return (nb_bytes);
}

char	*buf_to_str(t_buf *buf)
{
	char	*str;
	size_t	i;

	str = (char *)malloc((BUFFER_SIZE + 1)* sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE) // &&!='\n'
	{
		str[i] = buf->buf[i];
		i++;
	}
	str[i] = '\0';
	// free
	return (str);
}

char	*get_what_possible_from_buf(t_buf *buf)
{
	char	*str;
	size_t	i_str;
	size_t	i_buf;

	str = (char *)malloc((buf->end_old_content - buf->start_old_content + 2)* sizeof(char));
	if (str == NULL)
		return (NULL);
	i_str = 0;
	i_buf = buf->start_old_content;
	while (i_buf < buf->end_old_content)
	{
		str[i_str] = buf->buf[i_buf];
		if (str[i_str] == '\n')
		{
			str[i_str++] = '\0';
			if(i_buf < buf->end_old_content) // + 1?
			{
				buf->start_old_content = i_buf + 1;
				free (&str[i_str]);
			}
			else
			{
				buf->start_old_content = 0;
				buf->end_old_content = 0;
			}
			return (str);
		}
		i_str++;
		i_buf++;
	}
	str[i_str++] = '\0';
	if(i_buf < buf->end_old_content) // + 1?
		{
			buf->start_old_content = i_buf + 1;
			free (&str[i_str]);
		}
	else
		{
			buf->start_old_content = 0;
			buf->end_old_content = 0;
		}
	return (str);
}

char *get_next_line(int fd)
{
	t_buf		*buf;
	ssize_t	nb_bytes;

	buf = initialize_buf();
	if (buf == NULL)
		return (NULL);
	// nb_bytes = read_to_buf(fd, buf);
	printf("%s\n",get_what_possible_from_buf(buf));
	read_to_buf(fd, buf);
	printf("%s\n",buf_to_str(buf));
	//read_to_buf(fd, buf);
	//printf("%s\n",buf_to_str(buf));
	if (nb_bytes <= 0)
		return (NULL);
	// free buf
	return (buf_to_str(buf));
}
