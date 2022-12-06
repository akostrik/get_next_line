/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/06 18:35:16 by akostrik         ###   ########.fr       */
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

ssize_t	read_to_new_buf(int fd, t_buf	**new_buf)
{
	ssize_t	nb_bytes;
	ssize_t	i;

 	*new_buf = (t_buf *)malloc(sizeof(t_buf));
	if (new_buf == NULL)
		return ((ssize_t)(-1));
	//printf("1) new_buf = %p -> %p\n",new_buf,*new_buf);
	(*new_buf)->next = NULL;
	(*new_buf)->pos_1st_newline = -1;
	(*new_buf)->str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if ((*new_buf)->str == NULL)
		return (-1);
	nb_bytes = read(fd, (*new_buf)->str, BUFFER_SIZE);
	if (nb_bytes == -1)
		return (-1);
	if (nb_bytes == 0)
		return (0);
	i = 0;
	while (i < nb_bytes)
	{
		if ((*new_buf)->str[i] == '\n')
		{
			(*new_buf)->pos_1st_newline = i;
			break;
		}
		i++;
	}
	return (nb_bytes);
}

void	add_to_end(t_buf **lst_buf, t_buf **new_buf)
{
	t_buf	*cour;

	//printf("2) lst_buf = %p -> %p\n",lst_buf,*lst_buf);
	if (*lst_buf == NULL)
	{
		*lst_buf = *new_buf;
		//printf("3) lst_buf = %p -> %p\n",lst_buf,*lst_buf);
		return ;
	}
	cour = *lst_buf;
	while (cour -> next != NULL)
		cour = cour -> next;
	cour -> next = *new_buf;
}

char *concat_buffers_and_update_lst(t_buf **lst_buf)
{
	t_buf	*cour;
	size_t	len;
	size_t	i_str;
	ssize_t	i_buf;
	char		*str;

	printf("f. concat\n");
	cour = *lst_buf;
	len = 0;
	printf("cour -> next != NULL ? cour = %p\n", cour);
	printf("%d\n", cour -> next != NULL);
	while (cour -> next != NULL && cour -> pos_1st_newline == -1)
	{
		len += BUFFER_SIZE;
		cour = cour -> next;
	}
	len += (cour -> pos_1st_newline) + 1;
	printf("f. concat len = %zu\n",len);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	cour = *lst_buf;
	i_str = 0;
	while (cour -> next != NULL)
	{
		i_buf = 0;
		while (i_buf < BUFFER_SIZE)
		{
			str[i_str] = cour -> str[i_buf];
			i_str++;
			i_buf++;
		}
		printf("* str = %s\n",str);
		if (cour -> pos_1st_newline != -1)
			break ;
		cour = cour -> next;
	}
	i_buf = 0;
	printf("while %zu < %zd\n",i_buf, cour -> pos_1st_newline);
	while (i_buf < cour -> pos_1st_newline)
	{
		str[i_str] = cour -> str[i_buf];
		i_str++;
		i_buf++;
		//printf("* str = %s\n",str);
	}
	str[i_str] = '\0';
	printf("f. concat return %s\n",str);
	return (str);
}

char *get_next_line(int fd)
{
	t_buf		**lst_buf;
	t_buf		**new_buf;
	ssize_t	nb_bytes;
	char		*str;

	lst_buf = (t_buf **)malloc(sizeof(t_buf *));
	if (lst_buf == NULL)
		return (NULL);
	new_buf = (t_buf **)malloc(sizeof(t_buf*));
	if (new_buf == NULL)
		return (NULL);
	while (1)
	{
		printf("***\n");
		nb_bytes = read_to_new_buf(fd, new_buf);
		//printf("2) new_buf = %p -> %p\n",new_buf,*new_buf);
		printf("nb_bytes = %zu\n",nb_bytes);
		//printf("(*new_buf)->pos_1st_newline = %zu\n",(*new_buf)->pos_1st_newline);
		if (nb_bytes == -1)
			return (NULL);
		if (nb_bytes == 0)
			break ;
		//printf("1) lst_buf = %p -> %p\n",lst_buf,*lst_buf);
		add_to_end(lst_buf, new_buf);
		//printf("*) lst_buf = %p -> %p\n",lst_buf,*lst_buf);
		if ((*new_buf)->pos_1st_newline != -1)
		{
			break ;
		}
	}
	str = concat_buffers_and_update_lst(lst_buf);
	// free lst_buf
	return (str);
}
