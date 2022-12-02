#include "get_next_line.h"

/*
int	add_to_end(t_text_portion **lst, char *buf)
	{
	t_text_portion	*new_elt;
	t_text_portion	*cour;

	new_elt = (t_text_portion *)malloc(sizeof(t_text_portion));
	if (new_elt == NULL)
		return (0);
	new_elt -> text = ;
	new_elt -> next = NULL;
	if (*lst == NULL)
		*lst = new_elt;
	else
	{
		cour = *lst;
		while (cour -> next != NULL)
			cour = cour -> next;
		cour -> next = new_elt;
	}
	return (1);
}

t_text_portion	**create_list(int fd, char *buf)
{
	t_text_portion	**lst;

	lst = (t_text_portion **)malloc(sizeof(t_text_portion *));
	if (lst == NULL)
		return (NULL);
	*lst = NULL;
	while (1)
	{
		nb_read_bytes = read (fd, buf, BUFFER_SIZE);
		if (nb_read_bytes == -1)
			return (NULL);
		if (nb_read_bytes == 0)
			return (lst) ; //
		add_to_end(lst, buf);
	}
	return (lst);
}

void	destroy_list(t_text_portion ***lst)
{
	t_text_portion	*to_destroy;

	if (*lst == NULL)
		return ;
	while (**lst != NULL)
	{
		to_destroy = **lst;
		**lst = (**lst)-> next;
		free(to_destroy);
	}
	free(*lst);
}
*/