#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <wchar.h>
# include <stdarg.h>
# define FT_PRINTF_SHARP (1)
# define FT_PRINTF_ZERO (1 << 1)
# define FT_PRINTF_MINUS (1 << 2)
# define FT_PRINTF_SPACE (1 << 3)
# define FT_PRINTF_PLUS (1 << 4)

typedef struct	s_printf_arg
{
	long long int			val_i;
	unsigned long long int	val_ui;
	double					val_d;
	void					*ptr;
	wchar_t					val_wc;
	struct s_printf_arg		*next;
}				t_printf_arg;

typedef struct	s_printf_elem
{
	int					pos;
	t_printf_arg		*arg;
	char				conv_type;
	char				length_mod;
	char				flags;
	int					width;
	int					width_pos;
	char				width_seted;
	int					precision;
	int					precision_pos;
	char				precision_seted;
	char				*raw_str;
	struct s_printf_elem	*next;
}				t_printf_elem;

int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);

t_printf_elem	*ft_parse(char *fmt, int *pos);
t_printf_elem	*ft_parse_spec(char **fmt, int *pos);
int				ft_parse_is_conv_spec(char c);
t_printf_elem	*ft_printf_elem_new(void);
char			ft_parse_len_mod(char **fmt);
char			ft_parse_flag(char **fmt);
int				ft_parse_get_number(char **str);
int				ft_parse_is_reference(char *str);

t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos);
void			ft_push_args(t_printf_elem *els, t_printf_arg *args);

int				ft_display(int fd, t_printf_elem *els);
int				ft_display_raw(int fd, t_printf_elem *el);
int				ft_display_perc(int fd, t_printf_elem *el);
int				ft_display_x(int fd, t_printf_elem *el);
int				ft_display_X(int fd, t_printf_elem *el);
int				ft_display_s(int fd, t_printf_elem *el);
int				ft_display_c(int fd, t_printf_elem *el);
int				ft_display_o(int fd, t_printf_elem *el);
int				ft_display_di(int fd, t_printf_elem *el);
int				ft_display_u(int fd, t_printf_elem *el);
#endif