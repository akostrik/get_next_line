/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:18 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/01 17:07:07 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Repeated calls to get_next_line() let the text file fd, one line at a time
// Returns the line read from file/stdin / NULL nothing to read / NULL error
// A new line -> to return the current line
// Read as little as possible each time get_next_line() is called
// File changed since the last call whereas read didn’t reach EOF -> undef. behavior
// Binary file -> undef. behavior

// Don’t read the whole file and then process each line
// YES read malloc free
// NO lseek() libft 
// The helper functions in get_next_line_utils.c

// BUFFER_SIZE = 9999? 10000000?
// The buffer size and the line size can be of very different values
// The buffer size will be modified by evaluators / Moulinette
// compiler -D BUFFER_SIZE=n for read
// Cette macro définie à l’invocation du compilateur 
// Certains compilateurs permettent de définir des macros sans paramètres 
// A l'invocation du compilateur => une macro n'est nulle part définie dans 
// le source. La définition se fera à l'invocation du compilateur
// -D name=definition The contents of definition are tokenized and 
// processed as if they appeared during translation phase three in #define
// In particular, the definition will be truncated by embedded newline characters
// Содержание definition маркируется и обрабатывается, как будто они появились
// во время фазы перевода три в ‘#define’ директива. 
// В частности, определение является усеченным встроенными символами новой строки.

// ssize_t read(int fildes, void *buf, size_t nbyte)
// число от 1 до BUFFER_SIZE - число реально записанных байтов
// 0 EOF
// -1 ошибка

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char						*buf;
	ssize_t					nb_read_bytes;
	t_text_portion	**list;

	printf("get_next_line %d, buffer size = %d\n",fd,BUFFER_SIZE);
	buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buf == NULL)
		return (NULL);
	list = create_list(fd, buf);
	if (list == NULL)
		return (NULL);
	return ("abc");
}
