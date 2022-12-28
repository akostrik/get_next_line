/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/28 01:39:31 by akostrik         ###   ########.fr       */
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

/* void	print_lst_buf(t_buf **lst)
{
	t_buf	*b;
	ssize_t	i;
	ssize_t	j;

	b = *lst;
	if (b == NULL)
	{
		printf("empty buffer\n");
		return ;
	}
	j = 0;
	while (b != NULL)
	{
		printf("* %2zd * %p <-   ",j,b->prev);
		printf("%p [",b);
		i = 0;
		while (i <= b -> lst_pos)
		{
			if (b->str[i] == '\n')
				printf(" \\n ");
			else if (b->str[i] == EOF)
				{
					printf(" EOF ");
					break ;
				}
			else
				printf("%c",b->str[i]);
			i++;
		}
		printf("] %zu %zu %zd", b -> fst_pos, b -> nl_pos, b -> lst_pos);
		printf("   -> %p",b->next);
		printf("\n");
		b = b -> next;
		j++;
	}
}*/

void free_lst_buf(t_buf **lst)
{
	t_buf	*b;
	t_buf	*next;
	
	if (*lst != NULL)
		return ; // ?
	b = *lst;
	while (b != NULL)
	{
		next = b -> next;
		free(b->str);
		free(b);
		b = next;
	}
	*lst = NULL;
}

void fill_buf_and_add_to_lst(t_buf	*new, t_buf **lst, ssize_t	nb_bts)
{
	new -> fst_pos = 0;
	new -> lst_pos = nb_bts - 1;
	new -> nl_pos = new -> fst_pos;
	while (new -> nl_pos <= new -> lst_pos && new->str[new -> nl_pos] != '\n')
		(new -> nl_pos)++;
	if (nb_bts < BUFFER_SIZE)
	{
		new -> lst_pos ++;
		new -> str[nb_bts] = EOF;
	}
	new -> prev = NULL;
	if (*lst == NULL)
		new->next = NULL;
	else
	{
		new->next = *lst;
		if (*lst != NULL)
			(*lst) -> prev = new;
	}
	*lst = new;
}

ssize_t	read_buf_and_add_to_lst(int fd, t_buf **lst)
{
	ssize_t	nb_bts;
	t_buf		*new;

	new = (t_buf *)malloc(sizeof(t_buf));
	if (new == NULL)
		return (-1);
	new->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (new->str == NULL)
	{
		free(new);
		return (-1);
	}
	nb_bts = read(fd, new->str, BUFFER_SIZE);
	if (nb_bts == -1)
	{
		free(new -> str);
		free(new);
		return (-1);
	}
	fill_buf_and_add_to_lst(new, lst, nb_bts);
	return (nb_bts);
}

void f(t_buf **lst, t_buf	*b, char *s, ssize_t *i, size_t *i_s, t_buf *del)
{
	while (b != NULL)
	{
		*i = b -> fst_pos;
		while (*i <= b -> nl_pos && *i <= b -> lst_pos)
			s[(*i_s)++] = b -> str[(*i)++];
		b -> fst_pos = b -> nl_pos + 1;
		b -> nl_pos = b -> fst_pos;
		while (b -> nl_pos <= b -> lst_pos && b->str[b -> nl_pos] != '\n')
			b -> nl_pos++;
		if (*i <= b -> lst_pos)
			break ;
		if (b -> prev == NULL)
		{
			free(b->str);
			free(b);
			(*lst) = NULL;
			break;
		}
		del = b;
		b = b -> prev;
		b -> next = NULL;
		free(del->str);
		free(del);
	}
}

char *concat_buffers_and_update_lst(t_buf **lst)
{
	t_buf		*b;
	t_buf		*del;
	ssize_t	i;
	size_t	i_s;
	char		*s;

	if ((*lst) -> fst_pos == (*lst) -> lst_pos && (*lst)->str[(*lst)->lst_pos] \
	== EOF && (*lst)->next == NULL)
		return(NULL);
	i = 0;
	b = *lst;
	while (b != NULL && b -> next != NULL)
	{
		i += b -> nl_pos - b -> fst_pos;
		b = b -> next;
	}	
	i += b -> nl_pos - b -> fst_pos;
	s = (char *)malloc(i + 2);
	if (s == NULL)
		return (NULL);
	i_s = 0;
	del = NULL;
	f(lst, b, s, &i, &i_s, del);
	s[i_s] = '\0'; // i-2
	if (s[i_s - 1] == EOF) 
		s[i_s - 1] = '\0';
	return (s);
}

char *get_next_line(int fd)
{
	static t_buf	**lst = NULL;
	char					*str;

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
			free_lst_buf(lst);
			return (NULL);
		}
	}
	str = concat_buffers_and_update_lst(lst);
	if (*lst != NULL && (*lst) -> fst_pos ==  (*lst) -> lst_pos && (*lst)->str[(*lst)->lst_pos] == EOF)
		free_lst_buf(lst);
	return (str);
}
