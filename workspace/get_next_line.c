/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/14 14:05:27 by akostrik         ###   ########.fr       */
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

// free(указателю полученных не из malloc) например, free(p+10) - неопр поведение
// malloc в ячейки перед той, на которую указывает возвращаемый функцией указатель, записывает служебную информацию
// free(p+10) -> информация перед ячейкой (p+10) будет трактоваться как служебная

#include "get_next_line.h"
#include <string.h>

void	print_lst_buf(t_buf **lst_buf)
{
	t_buf	*cour;
	size_t	i;

	printf("buffers: ");
	if (lst_buf == NULL)
	{
		printf("list = NULL\n");
		return ;
	}
	cour = *lst_buf;
	while (cour != NULL)
	{
		i = cour -> pos_start;
		printf("[");
		while (i < BUFFER_SIZE)
		{
			if (cour->str[i] == '\n')
				printf("*");
			else
				printf("%c",cour->str[i]);
			i++;
		}
		printf("] ");
		cour = cour -> next;
	}
	printf("\n");
}

ssize_t	read_to_buf_and_add_to_lst(int fd, t_buf **lst_buf)
{
	ssize_t	nb_bytes;
	ssize_t	i;
	t_buf	*new_buf;

	new_buf = (t_buf *)malloc(sizeof(t_buf)); /// точно надо ?
	if (new_buf == NULL)
		return ((ssize_t)(-1));
	new_buf->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (new_buf->str == NULL)
		return ((ssize_t)(-1));
	new_buf->pos_start = 0;
	nb_bytes = read(fd, new_buf->str, BUFFER_SIZE);
	i = 0;
	while (i < nb_bytes && new_buf->str[i] != '\n')
		i++;
	new_buf -> pos_first_newline = i;
	new_buf -> prev = NULL;
	if (lst_buf == NULL)
		new_buf->next = NULL;
	else
	{
		new_buf->next = *lst_buf;
		if (*lst_buf != NULL)
			(*lst_buf) -> prev = new_buf;
	}
	*lst_buf = new_buf;
	return (nb_bytes);
}

size_t	len(t_buf **lst_buf)
{
	t_buf	*cour;
	size_t	len;

	if (lst_buf == NULL)
		return (0);
	cour = *lst_buf;
	while (cour != NULL)
	{
		len += cour -> pos_first_newline - cour -> pos_start;
		cour = cour -> next;
	}
	len++;
	return (len);
}

char *concat_buffers_and_update_lst(t_buf **lst_buf)
{
	t_buf	*cour;
	size_t	i_str;
	size_t	i_buf;
	char		*str;

	if (lst_buf == NULL || *lst_buf == NULL) //
		return ("");
	str = (char *)malloc(len(lst_buf) + 1);
	if (str == NULL)
		return (NULL);
	cour = *lst_buf;
	i_str = 0;
	while (cour != NULL && cour -> next != NULL)
		cour = cour -> next; ////////////////////////////
	while (cour != NULL)
	{
		i_buf = cour -> pos_start;
		while (i_buf < cour -> pos_first_newline)
		{
			str[i_str] = cour -> str[i_buf];
			i_str++;
			i_buf++;
		}
		cour = cour -> prev;
	}
	str[i_str] = '\0';
	// free
	return (str);
}

char *get_next_line(int fd)
{
	static t_buf	**lst_buf = NULL;
	ssize_t	nb_bytes;

	if (lst_buf == NULL)
	{
		lst_buf = (t_buf **)malloc(sizeof(t_buf *));
		if (lst_buf == NULL)
			return (NULL);
	}
	while (1)
	{
		nb_bytes = read_to_buf_and_add_to_lst(fd, lst_buf);
		if (nb_bytes == -1)
			return (NULL);
		if (nb_bytes == 0)
			break ;
		print_lst_buf(lst_buf);
		printf("\n");
		if ((*lst_buf)->pos_first_newline < BUFFER_SIZE)
			break ;
	}
	return (concat_buffers_and_update_lst(lst_buf));
}
