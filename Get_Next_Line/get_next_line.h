

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

typedef struct	s_fd_info
{
	char				*buff;
	size_t				length;	
	int					fd;
	struct s_fd_info	*next;
}				t_fd_info;

int		get_next_line(const int fd, char **line);

#endif