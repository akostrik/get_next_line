/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/11/30 21:55:54 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const char *s, ...)
{
	size_t	i;
	ssize_t	ret;
	va_list	list_args;
	int		fd;

	fd = 1;
	va_start(list_args, s);
	i = 0;
	ret = 0;
	while (i < ft_strlen((char *)s))
	{
		if (is_conversion(&s[i]) == 1)
		{
			ret += put_conversion(&s[i], list_args, fd);
			i++;
		}
		else
			ret += putchar_(s[i], fd);
		i++;
	}
	va_end(list_args);
	return ((int)ret);
}
