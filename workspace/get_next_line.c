/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/27 11:27:55 by akostrik         ###   ########.fr       */
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
	ssize_t	i;

	printf("buffers %p -> %p:\n",lst_buf, *lst_buf);
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
		printf("%p [",cour);
		i = 0;
		while (i <= cour -> last_pos)
		{
			if (cour->str[i] == '\n')
				printf("/");
			else if (cour->str[i] == EOF)
				{
					printf(" EOF ");
					break ;
				}
			else
				printf("%c",cour->str[i]);
			i++;
		}
		printf("] %zu %zu %zd", cour -> first_pos, cour -> first_newline_pos, cour -> last_pos);
		printf("\n");
		if ((*lst_buf)->str[(*lst_buf)->last_pos] == EOF)
			break;
		cour = cour -> next;
	}
}

size_t first_newline_pos_f(t_buf	*buf)
{
	ssize_t	i;

	if (buf -> last_pos == -1)
		return (1);
	i = buf -> first_pos;
	while (i <= buf -> last_pos && buf->str[i] != '\n') // EOF ?
		i++;
	return (i);
}

ssize_t	read_to_buf_and_add_to_lst(int fd, t_buf **lst_buf)
{
	ssize_t	nb_bytes;
	t_buf	*new_buf;

	new_buf = (t_buf *)malloc(sizeof(t_buf));
	if (new_buf == NULL)
	{
		return ((ssize_t)(-1));
	}
	printf("new_buf      + %p\n",new_buf);
	new_buf->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (new_buf->str == NULL)
	{
		printf("new_buf     - %p\n",new_buf);
		free(new_buf);
		return ((ssize_t)(-1));
	}
	printf("new_buf->str + %p\n",new_buf->str);
	nb_bytes = read(fd, new_buf->str, BUFFER_SIZE);
	if (nb_bytes == -1)
	{
		printf("new_buf->str - %p\n",new_buf->str);
		free(new_buf -> str);
		printf("new_buf      - %p\n",new_buf);
		free(new_buf);
		return ((ssize_t)(-1));
	}
	if (nb_bytes >= 0)
	{
		new_buf -> first_pos = 0;
		new_buf -> last_pos = nb_bytes - 1;
		new_buf -> first_newline_pos = first_newline_pos_f(new_buf);
		new_buf -> prev = NULL;
		if (nb_bytes < BUFFER_SIZE)
		{
		new_buf -> last_pos ++;
			new_buf -> str[nb_bytes] = EOF; ///
		}
		if (lst_buf == NULL)
			new_buf->next = NULL;
		else
		{
			new_buf->next = *lst_buf;
			if (*lst_buf != NULL)
				(*lst_buf) -> prev = new_buf;
		}
		*lst_buf = new_buf;
	}
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
	ssize_t	i; ///
	char		*str;

	//printf("concat_buffers\n");
	//print_lst_buf(lst_buf);
	if (*lst_buf == NULL)
		return ("");
	str = (char *)malloc(string_len(lst_buf));
	if (str == NULL)
		return (NULL);
	printf("str          + %p\n",str);
	i_str = 0;
	cour = *lst_buf;
	while (cour != NULL && cour -> next != NULL)
		cour = cour -> next;
	while (cour != NULL)
	{
		i = cour -> first_pos;
		while (i <= cour -> first_newline_pos && i <= cour -> last_pos)
		{
			str[i_str] = cour -> str[i];
			i_str++;
			i++;
		}
		cour -> first_pos = cour -> first_newline_pos + 1;
		cour -> first_newline_pos = first_newline_pos_f(cour);
		if (i <= cour -> last_pos) // в буфере что-то есть
			break;
		to_free = cour;
		printf("to_free->str - %p\n",to_free->str);
		free(to_free->str);
		printf("to_free      - %p\n",to_free);
		free(to_free);
		cour = cour -> prev;
		if (cour == NULL)
		{
			*lst_buf = NULL;
			break;
		}
		cour -> next = NULL;
	}
	str[i_str] = '\0';
	return (str);
}

void free_lst_buf(t_buf **lst_buf)
{
	t_buf	*cour;
	t_buf	*next;

	//printf("free lst buf\n");
	//print_lst_buf(lst_buf);
	if (lst_buf == NULL)
		return ;
	cour = *lst_buf;
	while (cour != NULL)
	{
		next = cour -> next;
		//if (i <= cour -> last_pos) // в буфере что-то есть
		printf("cour->str    - %p\n",cour->str);
		free(cour->str);
		printf("cour         - %p\n",cour);
		free(cour);
		cour = next;
		//printf("cour = %p\n",cour);
	}
	*lst_buf = NULL;
}

char *get_next_line(int fd)
{
	static t_buf	**lst_buf = NULL;
	ssize_t	nb_bytes;
	size_t		i;
	char		*str;

	if (lst_buf == NULL)
	{
		lst_buf = (t_buf **)malloc(sizeof(t_buf *));
		if (lst_buf == NULL)
			return (NULL);
		*lst_buf = NULL;
		printf("\nlst_buf      + %p -> %p\n-----------------------\n",lst_buf,*lst_buf);
	}
	i = 0;
	while (1)
	{
		if (lst_buf != NULL && *lst_buf != NULL && (*lst_buf)->first_newline_pos <= (*lst_buf) -> last_pos)
			break ;
		nb_bytes = read_to_buf_and_add_to_lst(fd, lst_buf);
		if (nb_bytes == -1)
		{
			free_lst_buf(lst_buf);
			return (NULL);
		}
		if (nb_bytes == 0 && i == 0)
		{
			//printf("empty file\n");
			free_lst_buf(lst_buf);
			return (NULL);
		}
		if (nb_bytes == 0)
			break ;
		if (*lst_buf != NULL && (*lst_buf)->str[(*lst_buf)->last_pos] == EOF)
			break ;
		i++;
	}
	str = concat_buffers_and_update_lst(lst_buf);
	if (*lst_buf != NULL && (*lst_buf)->str[(*lst_buf)->last_pos] == EOF)
	{
		free_lst_buf(lst_buf);
		//printf("lst_buf      - %p\n",lst_buf);
		//free (*lst_buf);
		//lst_buf = NULL;
	}
	return (str);
}
