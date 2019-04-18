

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 256
# include <string.h>

typedef struct	s_fd_info
{
	char				*buff;
	size_t				length;	
	int					fd;
	char				error;					
	struct s_fd_info	*next;
}				t_fd_info;

int		get_next_line(const int fd, char **line);

#endif