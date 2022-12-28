/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:42:08 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/28 02:28:03 by akostrik         ###   ########.fr       */
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

void	free_lst_buf(t_buf **l)
{
	t_buf	*b;
	t_buf	*next;

	if (*l != NULL)
		return ;
	b = *l;
	while (b != NULL)
	{
		next = b -> nxt;
		free(b->str);
		free(b);
		b = next;
	}
	*l = NULL;
}

void	fill_buf_and_add_to_lst(t_buf	*new, t_buf **l, ssize_t	nb_bts)
{
	new->p1 = 0;
	new->p2 = nb_bts - 1;
	new->p_nl = new->p1;
	while (new->p_nl <= new->p2 && new->str[new->p_nl] != '\n')
		(new->p_nl)++;
	if (nb_bts < BUFFER_SIZE)
	{
		new->p2 ++;
		new->str[nb_bts] = EOF;
	}
	new->prv = NULL;
	if (*l == NULL)
		new->nxt = NULL;
	else
	{
		new->nxt = *l;
		if (*l != NULL)
			(*l)->prv = new;
	}
	*l = new;
}

ssize_t	read_buf_and_add_to_lst(int fd, t_buf **l)
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
	fill_buf_and_add_to_lst(new, l, nb_bts);
	return (nb_bts);
}

void	func(t_buf **l, t_buf	*b, char *s, size_t *i_s)
{
	t_buf	*del;
	ssize_t	i;

	while (b != NULL)
	{
		i = b->p1;
		while (i <= b->p_nl && i <= b->p2)
			s[(*i_s)++] = b->str[i++];
		b->p1 = b->p_nl + 1;
		b->p_nl = b->p1;
		while (b->p_nl <= b->p2 && b->str[b->p_nl] != '\n')
			b -> p_nl++;
		if (i <= b->p2)
			break ;
		if (b->prv == NULL)
		{
			free(b->str);
			free(b);
			(*l) = NULL;
			break ;
		}
		del = b;
		b = b->prv;
		b->nxt = NULL;
		free(del->str);
		free(del);
	}
}

char	*concat_buffers_and_update_lst(t_buf **l)
{
	t_buf	*b;
	ssize_t	i;
	size_t	i_s;
	char	*s;

	if ((*l)->p1 == (*l)->p2 && (*l)->str[(*l)->p2] == EOF && (*l)->nxt == NULL)
		return (NULL);
	i = 0;
	b = *l;
	while (b != NULL && b -> nxt != NULL)
	{
		i += b -> p_nl - b -> p1;
		b = b -> nxt;
	}
	i += b -> p_nl - b -> p1;
	s = (char *)malloc(i + 2);
	if (s == NULL)
		return (NULL);
	i_s = 0;
	func(l, b, s, &i_s);
	s[i_s] = '\0';
	if (s[i_s - 1] == EOF)
		s[i_s - 1] = '\0';
	return (s);
}
