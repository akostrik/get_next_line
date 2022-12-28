/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:42:08 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/28 02:00:57 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	free_lst_buf(t_buf **lst)
{
	t_buf	*b;
	t_buf	*next;

	if (*lst != NULL)
		return ;
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

void	fill_buf_and_add_to_lst(t_buf	*new, t_buf **lst, ssize_t	nb_bts)
{
	new->fst_pos = 0;
	new->p2 = nb_bts - 1;
	new->p1 = new->fst_pos;
	while (new->p1 <= new->p2 && new->str[new->p1] != '\n')
		(new->p1)++;
	if (nb_bts < BUFFER_SIZE)
	{
		new->p2 ++;
		new->str[nb_bts] = EOF;
	}
	new->prev = NULL;
	if (*lst == NULL)
		new->next = NULL;
	else
	{
		new->next = *lst;
		if (*lst != NULL)
			(*lst)->prev = new;
	}
	*lst = new;
}

ssize_t	read_buf_and_add_to_lst(int fd, t_buf **lst)
{
	ssize_t	nb_bts;
	t_buf	*new;

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
		free(new->str);
		free(new);
		return (-1);
	}
	fill_buf_and_add_to_lst(new, lst, nb_bts);
	return (nb_bts);
}

void	f(t_buf **lst, t_buf	*b, char *s, ssize_t *i, size_t *i_s, t_buf *del)
{
	while (b != NULL)
	{
		*i = b->fst_pos;
		while (*i <= b->p1 && *i <= b->p2)
			s[(*i_s)++] = b->str[(*i)++];
		b->fst_pos = b->p1 + 1;
		b->p1 = b->fst_pos;
		while (b->p1 <= b->p2 && b->str[b->p1] != '\n')
			b -> p1++;
		if (*i <= b->p2)
			break ;
		if (b->prev == NULL)
		{
			free(b->str);
			free(b);
			(*lst) = NULL;
			break ;
		}
		del = b;
		b = b->prev;
		b->next = NULL;
		free(del->str);
		free(del);
	}
}

char	*concat_buffers_and_update_lst(t_buf **lst)
{
	t_buf	*b;
	t_buf	*del;
	ssize_t	i;
	size_t	i_s;
	char	*s;

	if ((*lst)->fst_pos == (*lst)->p2 && (*lst)->str[(*lst)->p2] \
	== EOF && (*lst)->next == NULL)
		return (NULL);
	i = 0;
	b = *lst;
	while (b != NULL && b -> next != NULL)
	{
		i += b -> p1 - b -> fst_pos;
		b = b -> next;
	}
	i += b -> p1 - b -> fst_pos;
	s = (char *)malloc(i + 2);
	if (s == NULL)
		return (NULL);
	i_s = 0;
	del = NULL;
	f(lst, b, s, &i, &i_s, del);
	s[i_s] = '\0';
	if (s[i_s - 1] == EOF)
		s[i_s - 1] = '\0';
	return (s);
}
