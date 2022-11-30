/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/11/30 23:42:24 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Repeated calls to get_next_line() let the text file fd, one line at a time
// Returns the line read from file, stdin / NULL nothing to read / NULL error
// A new line -> to return the current line
// Read as little as possible each time get_next_line() is called
// File changed since the last call whereas read didn’t reach the EOF -> undef. behavior
// Binary file -> undef. behavior

// Don’t read the whole file and then process each line
// YES read malloc free
// NO lseek() libft 
// The helper functions in get_next_line_utils.c	
// BUFFER_SIZE value is 9999? 10000000?
// The buffer size and the line size can be of very different values
// The buffer size will be modified by evaluators / Moulinette
// compiler -D BUFFER_SIZE=n for read // macros

// ssize_t read(int fildes, void *buf, size_t nbyte)

#include "get_next_line.h"

char *get_next_line(int fd)
{
	printf("get_next_line %d, buffer size = %d\n",fd,BUFFER_SIZE);
	return ("abc");
}
