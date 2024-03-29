/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/31 14:39:35 by akostrik         ###   ########.fr       */
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
// File changed since the last call whereas read didn’t reach EOF -> undef beh
// Binary file -> undef. behavior
// Don’t read the whole file and then process each line

// free(указателю не из malloc) например, free(p+10) - неопр поведение
// malloc  записывает информацию в ячейку перед ячейкой с указателем
// free(p+10) -> информация перед яч. (p+10) будет трактоваться как служебная

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buf	**l = NULL;
	char			*s;

	if (BUFFER_SIZE < 1)
		return (NULL);
	if (fd < 0)
		return (NULL);
	if (l == NULL)
	{
		l = (t_buf **)malloc(sizeof(t_buf *));
		if (l == NULL)
			return (NULL);
		*l = NULL;
	}
	while (*l == NULL || ((*l)->nl > (*l)->e && (*l)->s[(*l)->e] != EOF))
		if (read_buf_and_add_to_l(fd, l) == -1)
			return (free_l_and_return_null(&l));
	s = concat_buffers_and_update_lst(l);
	if (s == NULL)
		return (free_l_and_return_null(&l));
	if (*l != NULL && (*l)->b == (*l)->e && (*l)->s[(*l)->e] == EOF)
		free_l_and_return_null(&l);
	return (s);
}

// int main ()
// {
// 	int fd;
// 	char *line;
// 	int to_continue;

// 	fd = open("my.fdf", O_RDONLY);
// 	to_continue = 1;
// 	line = get_next_line(fd);
// 	printf("[%s]\n", line);
// 	if (line == NULL)
// 		to_continue = 0;
// 	free(line);
// 	while (to_continue == 1)
// 	{
// 		line = get_next_line(fd);
// 		if (line != NULL)
// 			printf("[%s]\n", line);
// 		if (line == NULL)
// 			to_continue = 0;
// 		free(line);
// 	}
// 	printf("\n");
// 	return (0);
// }
