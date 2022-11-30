/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/11/30 22:14:47 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the line read from file or stdin / NULL nothing else to read / NULL error
// An undefined behavior if the file fd changed since the last call whereas read() didn’t reach the end of file

// An undefined behavior when reading a binary file
// BUFFER_SIZE value is 9999? 10000000?
// Read as little as possible each time get_next_line() is called. If you 
// encounter a new line -> to return the current line.
// Don’t read the whole file and then process each line.

// read malloc free
// lseek(), libft forbidden
// all the helper functions in get_next_line_utils.c	

// Repeated calls to get_next_line() let read the text file pointed to by 
// the file descriptor, one line at a time

// read files in get_next_line(), compiler -D BUFFER_SIZE=n, buffer size read()
// The buffer size value will be modified by evaluators and the Moulinette

// The buffer size and the line size can be of very different values

#include "get_next_line.h"

char *get_next_line(int fd);
{
	size_t	i;
	ssize_t	ret;

	i = 0;
	ret = 0;
	return ((int)ret);
}
