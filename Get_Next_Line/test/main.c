#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(void)
{
	int		fd1, fd2, fd3;
	char	name1[] = "text1.txt";
	char	name2[] = "text2.txt";
	char	name3[] = "text3.txt";
	char	*readed_line = NULL;
	int		result;

	fd1 = open(name1, O_RDONLY);
	fd2 = open(name2, O_RDONLY);
	fd3 = open(name3, O_RDONLY);

	result = get_next_line(fd2, &readed_line);
	printf("%s(%d): %s\n", name2, result, readed_line);

	//result = get_next_line(fd3, &readed_line);
	//printf("%s(%d): %s\n", name3, result, readed_line);

	result = get_next_line(fd2, &readed_line);
	printf("%s(%d): %s\n", name2, result, readed_line);

	result = get_next_line(fd2, &readed_line);
	printf("%s(%d): %s\n", name2, result, readed_line);

	result = get_next_line(fd2, &readed_line);
	printf("%s(%d): %s\n", name2, result, readed_line);

	//result = get_next_line(fd2, &readed_line);
	//printf("%s(%d): %s\n", name2, result, readed_line);

	close(fd1);
	close(fd2);
	close(fd3);
}