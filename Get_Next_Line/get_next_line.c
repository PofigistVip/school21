#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_realloc(void *src, size_t old_size, size_t new_size);
void	*ft_memchr(const void *s, int c, size_t n);

static t_fd_info	*get_fd_info(t_fd_info *start, const int fd)
{
	if (start == NULL)
		return (NULL);
	while (start)
	{
		if (start->fd == fd)
			return (start);
		start = start->next;
	}
	return (NULL);
}

static t_fd_info	*fd_info_new(t_fd_info **start, const int fd)
{
	t_fd_info	*new;

	new = (t_fd_info*)malloc(sizeof(t_fd_info));
	new->fd = fd;
	new->next = *start;
	new->length = 0;
	*start = new;
	return (new);
}

static void			get_line_from_fd(t_fd_info *info, char **line, char* new_line_pos)
{
	size_t	len;
	char	*temp;

	if (new_line_pos == NULL)
		len = info->length;
	else
		len = new_line_pos - info->buff;
	*line = (char*)malloc(len + 1);
	(*line)[len] = '\0';
	ft_memcpy(*line, info->buff, len);
	
	if (new_line_pos == NULL)
		++len;
	info->length = info->length - len - 2;
	temp = (char*)malloc(info->length);
	ft_memcpy(temp, info->buff + len + 2, info->length);
	free(info->buff);
	info->buff = temp;
}

static char	*read_to_newl(t_fd_info *info, const int fd)
{
	char	buff[BUFF_SIZE];
	int		readed;
	char	*new_line_pos;

	while ((readed = read(fd, buff, BUFF_SIZE)) > 0)
	{
		//
		info->buff = ft_realloc(info->buff, info->length, info->length + readed);
		ft_memcpy(info->buff + info->length, buff, readed);
		info->length += readed;
		new_line_pos = (char*)ft_memchr(info->buff, (int)'\n', info->length);
		if (new_line_pos != NULL)
			break ;
	}
	if (readed != 0)
		return (new_line_pos);
	else if (readed	== 0)
	{
		//EOF
		return (NULL);
	}
	else
		return (NULL);//ERROR
}

#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	static t_fd_info	*start;
	t_fd_info			*info;
	char				*new_line_pos;

	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	info = get_fd_info(start, fd);
	if (info == NULL){
		info = fd_info_new(&start, fd);
	}
	//printf("%d\n", info->length);
	new_line_pos = (char*)ft_memchr(info->buff, (int)'\n', info->length);
	if (new_line_pos == NULL)
		new_line_pos = read_to_newl(info, fd);
	if (new_line_pos == NULL && info->length == 0)
	{
		*line = "";
		return (0); //reading complete
	}
	get_line_from_fd(info, line, new_line_pos);
	printf("Len: %d ", info->length);
	//printf("BUFFER: %s, LEN: %d\n", info->buff, info->length);
	return (1);
}