/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/28 01:29:50 by akostrik         ###   ########.fr       */
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
// Binary file -> undef. behaviorfv
// Don’t read the whole file and then process each line

// free(указателю не из malloc) например, free(p+10) - неопр поведение
// malloc  записывает информацию в ячейку перед ячейкой с указателем
// free(p+10) -> информация перед яч. (p+10) будет трактоваться как служебная

#include "get_next_line.h"
#include <string.h>
/*
void	print_lst_buf(t_buf **lst)
{
	t_buf	*cour;
	ssize_t	i;
	ssize_t	j;

	cour = *lst;
	if (cour == NULL)
	{
		printf("empty buffer\n");
		return ;
	}
	j = 0;
	while (cour != NULL)
	{
		printf("* %2zd * %p <-   ",j,cour->prev);
		printf("%p [",cour);
		i = 0;
		while (i <= cour -> lst_pos)
		{
			if (cour->str[i] == '\n')
				printf(" \\n ");
			else if (cour->str[i] == EOF)
				{
					printf(" EOF ");
					break ;
				}
			else
				printf("%c",cour->str[i]);
			i++;
		}
		printf("] %zu %zu %zd", cour -> fst_pos, cour -> nl_pos, cour -> lst_pos);
		printf("   -> %p",cour->next);
		printf("\n");
		cour = cour -> next;
		j++;
	}
}*/

void free_lst_buf(t_buf **lst)
{
	t_buf	*cour;
	t_buf	*next;
	
	if (*lst != NULL)
		return ; // ?
	cour = *lst;
	while (cour != NULL)
	{
		next = cour -> next;
		free(cour->str);
		free(cour);
		cour = next;
	}
	*lst = NULL;
}

void fill_buf_and_add_to_lst(t_buf	*new_buf, t_buf **lst, ssize_t	nb_bytes)
{
	new_buf -> fst_pos = 0;
	new_buf -> lst_pos = nb_bytes - 1;
	new_buf -> nl_pos = new_buf -> fst_pos;
	while (new_buf -> nl_pos <= new_buf -> lst_pos && new_buf->str[new_buf -> nl_pos] != '\n')
		(new_buf -> nl_pos)++;
	if (nb_bytes < BUFFER_SIZE)
	{
		new_buf -> lst_pos ++;
		new_buf -> str[nb_bytes] = EOF;
	}
	new_buf -> prev = NULL;
	if (*lst == NULL)
		new_buf->next = NULL;
	else
	{
		new_buf->next = *lst;
		if (*lst != NULL)
			(*lst) -> prev = new_buf;
	}
	*lst = new_buf;
}

ssize_t	read_buf_and_add_to_lst(int fd, t_buf **lst)
{
	ssize_t	nb_bytes;
	t_buf	*new_buf;

	new_buf = (t_buf *)malloc(sizeof(t_buf));
	if (new_buf == NULL)
		return (-1);
	new_buf->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (new_buf->str == NULL)
	{
		free(new_buf);
		return (-1);
	}
	nb_bytes = read(fd, new_buf->str, BUFFER_SIZE);
	if (nb_bytes == -1)
	{
		free(new_buf -> str);
		free(new_buf);
		return (-1);
	}
	fill_buf_and_add_to_lst(new_buf, lst, nb_bytes);
	return (nb_bytes);
}

void concat_update(t_buf **lst, t_buf	*cour, char *str, ssize_t *i, size_t *i_str, t_buf *free)
{
	while (cour != NULL) 
	{
		*i = cour -> fst_pos;
		while (*i <= cour -> nl_pos && *i <= cour -> lst_pos)
			str[(*i_str)++] = cour -> str[(*i)++];
		cour -> fst_pos = cour -> nl_pos + 1;
		cour -> nl_pos = cour -> fst_pos;
		while (cour -> nl_pos <= cour -> lst_pos && cour->str[cour -> nl_pos] != '\n')
			cour -> nl_pos++;
		if (*i <= cour -> lst_pos)
				break ;
		if (cour -> prev == NULL)
		{
			free(cour->str);
			free(cour);
			(*lst) = NULL;
			break;
		}
		free = cour;
		cour = cour -> prev;
		cour -> next = NULL;
		free(free->str);
		free(free);
	}
}

char *concat_buffers_and_update_lst(t_buf **lst)
{
	t_buf	*cour;
	t_buf	*free;
	ssize_t	i;
	size_t	i_str;
	char		*str;

	if ((*lst) -> fst_pos == (*lst) -> lst_pos && (*lst)->str[(*lst)->lst_pos] == EOF && (*lst)->next == NULL)
		return(NULL);
	i = 0;
	cour = *lst;
	while (cour != NULL && cour -> next != NULL)
	{
		i += cour -> nl_pos - cour -> fst_pos;
		cour = cour -> next;
	}	
	i += cour -> nl_pos - cour -> fst_pos;
	str = (char *)malloc(i + 2);
	if (str == NULL)
		return (NULL);
	i_str = 0;
	free = NULL;
	concat_update(lst, cour, str, &i, &i_str, free);
	str[i_str] = '\0'; // i-2
	if (str[i_str - 1] == EOF) 
		str[i_str - 1] = '\0';
	return (str);
}

char *get_next_line(int fd)
{
	static t_buf	**lst = NULL;
	char		*str;

	if (lst == NULL)
	{
		lst = (t_buf **)malloc(sizeof(t_buf *));
		if (lst == NULL)
			return (NULL);
		*lst = NULL;
	}
	while (1)
	{
		if (*lst != NULL && (*lst)->nl_pos <= (*lst) -> lst_pos)
			break ;
		if (*lst != NULL && (*lst)->str[(*lst)->lst_pos] == EOF)
			break ;
		if (read_buf_and_add_to_lst(fd, lst) == -1)
		{
			//free_lst_buf(lst_buf);
			return (NULL);
		}
	}
	str = concat_buffers_and_update_lst(lst);
	if (*lst != NULL && (*lst) -> fst_pos ==  (*lst) -> lst_pos && (*lst)->str[(*lst)->lst_pos] == EOF)
		free_lst_buf(lst);
	return (str);
}
