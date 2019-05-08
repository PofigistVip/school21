#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <wchar.h>

typedef struct	s_printf_elem
{
	int					pos;
	char				conv_type;
	char				length_mod;
	char				flags;
	int					width;
	int					width_pos;
	int					precision;
	int					precision_pos;
	char				*raw_str;
	struct s_print_elem	*next;
}				t_printf_elem;

typedef struct	s_printf_arg
{
	long long int			val_i;
	unsigned long long int	val_ui;
	double					val_d;
	void					*ptr;
	wchar_t					*val_wc;
	struct s_printf_arg		*next;
}				t_printf_arg;

int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);

t_printf_elem	*ft_parse(const char *fmt, int *pos);
char	ft_parse_len_mod(char **fmt);
char	ft_parse_flag(char **fmt);
int		ft_parse_get_number(char **str);
int		ft_parse_is_reference(char *str);
#endif