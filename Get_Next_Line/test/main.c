#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

static				void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(void)
{
	int		fd1;
	char	name1[] = "text1.txt";
	char	*line;
	int		status;

	fd1 = open(name1, O_RDONLY);
	while ((status = get_next_line(fd1, &line)) > 0)
	{
		ft_putstr(line);
		ft_putstr("\n");
	}
	if (status != 0)
	{
		ft_putstr("Finished with error\n");
	}
	close(fd1);
}