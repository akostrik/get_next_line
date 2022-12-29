/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:42:08 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/29 11:37:21 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	print_l(t_buf **l, char *comment)
{
	t_buf	*b;
	ssize_t	i;
	ssize_t	j;

	printf("\n%s:\n",comment);
	if (l == NULL)
	{
		printf("buf = NULL\n");
		return ;
	}
	b = *l;
	if (b == NULL)
	{
		printf("buf -> NULL\n");
		return ;
	}
	j = 0;
	while (b != NULL)
	{
		printf("* %2zd * %p <-   ", j, b->prv);
		printf("%p [",b);
		i = 0;
		while (i <= b->p2)
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
		printf("] %zu %zu %zd", b->p1, b->pnl, b->p2);
		printf("   -> %p", b->nxt);
		printf("\n");
		b = b -> nxt;
		j++;
	}
}

void	free_l(t_buf **l)
{
	t_buf	*b;
	t_buf	*next;

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

void	fill_buf_and_add_to_l(t_buf	*new, t_buf **l, ssize_t	nb_bts)
{
	new->p1 = 0;
	new->p2 = nb_bts - 1;
	new->pnl = new->p1;
	while (new->pnl <= new->p2 && new->str[new->pnl] != '\n')
		(new->pnl)++;
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

ssize_t	read_buf_and_add_to_l(int fd, t_buf **l)
{
	ssize_t	nb_bts;
	t_buf	*new;

	new = (t_buf *)malloc(sizeof(t_buf)); // 48 bytes
	if (new == NULL)
		return (-1);
	new->str = (char *)malloc(BUFFER_SIZE); // BUFFER_SIZE bytes
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
	fill_buf_and_add_to_l(new, l, nb_bts);
	return (nb_bts);
}

void	concat_update(t_buf **l, t_buf	*b, char *s, size_t *i_s)
{
	t_buf	*del;
	ssize_t	i;

	while (b != NULL)
	{
		i = b->p1;
		while (i <= b->pnl && i <= b->p2)
			s[(*i_s)++] = b->str[i++];
		b->p1 = b->pnl + 1;
		b->pnl = b->p1;
		while (b->pnl <= b->p2 && b->str[b->pnl] != '\n')
			b->pnl++;
		if (i <= b->p2)
			break ;
		del = b;
		b = b->prv;
		*l = del->prv;
		free(del->str);
		free(del);
		if (b == NULL)
			break ;
		b->nxt = NULL;
	}
}

char	*concat_buffers_and_update_lst(t_buf ***l)
{
	t_buf	*b;
	ssize_t	i;
	char	*s;
	size_t	i_s;

	if ((**l)->p1 == (**l)->p2 && (**l)->str[(**l)->p2] == EOF && (**l)->nxt == NULL)
		return (NULL);
	i = 0;
	b = **l;
	while (b != NULL && b -> nxt != NULL)
	{
		i += b -> pnl - b -> p1;
		b = b -> nxt;
	}
	s = (char *)malloc(i + b -> pnl - b -> p1 + 2);
	if (s == NULL) 
	{
		free_l(*l);
		return (NULL);
	}
	i_s = 0;
	concat_update(*l, b, s, &i_s);
	s[i_s] = '\0';
	if (s[i_s - 1] == EOF)
		s[i_s - 1] = '\0';
	return (s);
}
