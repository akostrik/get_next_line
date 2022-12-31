/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:57:16 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/31 16:49:51 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "workspace/get_next_line.h"

// При ошибке открытия файла возвращается -1, errno:
// EACCES - нет прав на сам файл или на поиск в каталоге в котором он находится;
// ENOENT - файл не существует и не указан флаг O_CREAT;
// EEXIST - файл существует и указаны флаги O_CREAT+O_EXCL;
// EFAULT - плохой указатель на имя файла (например NULL);
// EISDIR - попытка открыть каталог;
// ELOOP  - символические ссылки создали кольцо в структуре каталогов.

int main(void)
{
	int	fd;
	char *s;

	fd = open("test_files/abc.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("can't open file\n");
		return (0);
	}

	printf("*************** THE FIRST FILE :\n");
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		free (s);
		s = get_next_line(fd);
	}
	printf("\n*************** The end");


	fd = open("test_files/abc2.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("can't open file\n");
		return (0);
	}

	printf("\n\n*************** THE SECOND FILE :\n");
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		free (s);
		s = get_next_line(fd);
	}
	printf("\n*************** The end\n");
}