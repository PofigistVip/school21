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
#endif