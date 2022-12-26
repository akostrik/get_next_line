/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/26 21:10:24 by akostrik         ###   ########.fr       */
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

	printf("buffers %p:\n",lst_buf);
	if (lst_buf == NULL)
	{
		printf("list = NULL\n");
		return ;
	}
	cour = *lst_buf;
	if (cour == NULL)
	{
		printf("empty\n");
		return ;
	}
	while (cour != NULL)
	{
		//printf("while\n");
		printf("%p ",cour);
		//printf("while\n");
		i = 0;
		while (i <= cour -> last_pos)
		{
			if (cour->str[i] == '\n')
				printf("/");
			else if (cour->str[i] == EOF)
				{
					printf(".");
					break ;
				}
			else
				printf("%c",cour->str[i]);
			i++;
		}
		printf(" %zu %zu %zu\n", cour -> first_pos, cour -> first_newline_pos, cour -> last_pos);
		cour = cour -> next;
	}
	printf("\n");
}

size_t first_newline_pos_f(t_buf	*buf)
{
	ssize_t	i;

	i = buf -> first_pos;
	while (i <= buf -> last_pos && buf->str[i] != '\n')
		i++;
	return (i);
}

ssize_t	read_to_buf_and_add_to_lst(int fd, t_buf **lst_buf)
{
	ssize_t	nb_bytes;
	t_buf	*new_buf;

	//printf("read_to_buf_and_add_to_lst\n");
	new_buf = (t_buf *)malloc(sizeof(t_buf)); /// точно надо ?
	if (new_buf == NULL)
		return ((ssize_t)(-1));
	new_buf->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (new_buf->str == NULL)
		return ((ssize_t)(-1));
	nb_bytes = read(fd, new_buf->str, BUFFER_SIZE);
	if (nb_bytes == 0)
	{
		// free
		return (0);
	}
	//printf("nb_bytes = %zu\n",nb_bytes);
	new_buf -> first_pos = 0;
	new_buf -> last_pos = nb_bytes - 1;
	new_buf -> first_newline_pos = first_newline_pos_f(new_buf);
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
	//printf("read_to_buf finished : ");
	//print_lst_buf(lst_buf);
	return (nb_bytes);
}

size_t	string_len(t_buf **lst_buf)
{
	t_buf	*cour;
	size_t	len;

	if (lst_buf == NULL)
		return (0);
	cour = *lst_buf;
	len = 0;
	while (cour != NULL)
	{
		len += cour -> first_newline_pos - cour -> first_pos;
		cour = cour -> next;
	}
	return (len + 1);
}

char *concat_buffers_and_update_lst(t_buf **lst_buf)
{
	t_buf	*cour;
	t_buf	*to_free;
	size_t	i_str;
	size_t	i;
	char		*str;

	if (lst_buf == NULL || *lst_buf == NULL)
		return ("");
	str = (char *)malloc(string_len(lst_buf));
	if (str == NULL)
		return (NULL);
	cour = *lst_buf;
	i_str = 0;
	while (cour != NULL && cour -> next != NULL)
		cour = cour -> next;
	while (cour != NULL)
	{
		i = cour -> first_pos;
		while (i < cour -> first_newline_pos && i <= cour -> last_pos)
		{
			str[i_str] = cour -> str[i];
			i_str++;
			i++;
		}
		cour -> first_pos = cour -> first_newline_pos + 1;
		cour -> first_newline_pos = first_newline_pos_f(cour);
		to_free = cour;
		cour = cour -> prev;
		//printf("free %p\n",to_free);
		//if ()
		//	free(to_free -> str); ////////////////////////////////
		//free(to_free); // free(next)
		if (cour != NULL)
			cour -> next = NULL;
		if (cour != NULL && i < cour -> last_pos)
			break; // after free
	}
	str[i_str] = '\0';
	return (str);
}

char *get_next_line(int fd)
{
	static t_buf	**lst_buf = NULL;
	ssize_t	nb_bytes;
	int	first_iteration;

	if (lst_buf == NULL)
	{
		lst_buf = (t_buf **)malloc(sizeof(t_buf *));
		if (lst_buf == NULL)
			return (NULL);
	}
	first_iteration = 1;
	while (1)
	{
		if (*lst_buf != NULL && (*lst_buf)->first_newline_pos <= (*lst_buf) -> last_pos)
			break ;
		nb_bytes = read_to_buf_and_add_to_lst(fd, lst_buf);
		if (nb_bytes == -1)
			return (NULL);
		if (nb_bytes == 0 && first_iteration == 1)
			return (NULL);
		if (nb_bytes == 0)
			break ;
		first_iteration = 0;
	}
	return (concat_buffers_and_update_lst(lst_buf));
}
