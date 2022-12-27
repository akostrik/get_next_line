/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:57:16 by akostrik          #+#    #+#             */
/*   Updated: 2022/12/27 17:36:25 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "workspace/get_next_line.h"

//static char *get_next_line(int fd);

int main(void)
{
	int	fd;

	// fd = open("test_files/brassens.txt", O_RDONLY);
	fd = open("test_files/abc.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("can't open file\n");
		return (1); // 0 ?
	}
// При ошибке открытия файла возвращается -1, errno:
// EACCES - нет прав на сам файл или на поиск в каталоге в котором он находится;
// ENOENT - файл не существует и не указан флаг O_CREAT;
// EEXIST - файл существует и указаны флаги O_CREAT+O_EXCL;
// EFAULT - плохой указатель на имя файла (например NULL);
// EISDIR - попытка открыть каталог;
// ELOOP - символические ссылки создали кольцо в структуре каталогов.

	printf("[%s]",get_next_line(fd));
	printf("\n-----------------\n");
	printf("[%s]\n",get_next_line(fd));
	printf("\n-----------------\n");
	printf("[%s]\n",get_next_line(fd));
}