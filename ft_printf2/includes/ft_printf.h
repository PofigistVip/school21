#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <wchar.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"
# define FT_PRINTF_SHARP (1)
# define FT_PRINTF_ZERO (1 << 1)
# define FT_PRINTF_MINUS (1 << 2)
# define FT_PRINTF_SPACE (1 << 3)
# define FT_PRINTF_PLUS (1 << 4)
# define FT_INFNUM_SIZE 1250
# define FT_LONGNUMBER_SIZE 4125
# define FT_LONGNUMBER_DIG_ON_INT 4
# define FT_LONGNUMBER_BASE 10000

typedef struct	s_printf_arg
{
	long long int			val_i;
	unsigned long long int	val_ui;
	long double				val_d;
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

typedef struct	s_infnum
{
	char	*digits;
	char	sign;
	size_t	size;
	size_t	max_pos;
	size_t	min_pos;
}				t_infnum;

typedef struct	s_double_keeper
{
	__uint128_t		sign;
	__int128_t		mantissa;
	__uint128_t		fraction;
	t_lstr			*int_part;
	t_lstr			*dec_part;
}				t_double_keeper;

typedef struct	s_longnumber
{
	char	is_decimal;
	int		dec_end_on;
	int		digits[FT_LONGNUMBER_SIZE];
}				t_longnumber;

int				ft_printf(const char *format, ...);
int				ft_fprintf(int fd, const char *format, ...);

t_printf_elem	*ft_parse(char *fmt, int *pos);
t_printf_elem	*ft_parse_spec(char **fmt, int *pos, char *add);
int				ft_parse_is_conv_spec(char c);
t_printf_elem	*ft_printf_elem_new(void);
char			ft_parse_len_mod(char **fmt);
char			ft_parse_flag(char **fmt);
int				ft_parse_get_number(char **str);
t_printf_elem	*ft_parse_rawstr(char **fmt);
int				ft_parse_is_reference(char *str);

t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos);
void			ft_push_args(t_printf_elem *els, t_printf_arg *args);

void			ft_putwchar(t_lstr *lstr, wchar_t wc);
int				ft_byte_size(int num);

int				ft_display(int fd, t_printf_elem *els, t_printf_arg *args);
int				ft_display_raw(int fd, t_printf_elem *el);
int				ft_display_perc(int fd, t_printf_elem *el);
int				ft_display_x(int fd, t_printf_elem *el);
int				ft_display_big_x(int fd, t_printf_elem *el);
int				ft_display_s(int fd, t_printf_elem *el);
int				ft_display_c(int fd, t_printf_elem *el);
int				ft_display_o(int fd, t_printf_elem *el);
int				ft_display_di(int fd, t_printf_elem *el);
int				ft_display_u(int fd, t_printf_elem *el);
int				ft_display_big_u(int fd, t_printf_elem *el);
int				ft_display_p(int fd, t_printf_elem *el);
int				ft_display_big_o(int fd, t_printf_elem *el);
int				ft_display_big_d(int fd, t_printf_elem *el);
int				ft_display_big_c(int fd, t_printf_elem *el);
int				ft_display_big_s(int fd, t_printf_elem *el);
int				ft_display_f_big_f(int fd, t_printf_elem *el);
int				ft_display_unknown(int fd, t_printf_elem *el);

t_infnum	*ft_infnum_create_num(int number, size_t size);
t_infnum	*ft_infnum_mul(t_infnum *a, t_infnum *b);
void		ft_infnum_destroy(t_infnum **inum);
t_infnum	*ft_infnum_create_empty(size_t size);
t_infnum	*ft_infnum_add(t_infnum *a, t_infnum *b, int destroy_a, int destroy_b);
t_lstr		*ft_infnum_get(t_infnum *inum);
void		ft_infnum_calc_max_pos(t_infnum *inum);

//test
char			*ft_lnum_get_dec(t_longnumber *lnum);
char			*ft_lnum_get(t_longnumber *lnum);
void			ft_lnum_make_decimal(t_longnumber **lnum, int shift);
t_longnumber	*ft_lnum_pow(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b);
t_longnumber	*ft_lnum_mul(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b);
t_longnumber	*ft_lnum_sub(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b);
t_longnumber	*ft_lnum_add(t_longnumber *a, t_longnumber *b, int dst_a, int dst_b);
int				ft_lnum_length(t_longnumber *lnum);
t_longnumber	*ft_lnum_new_int(int number);
t_longnumber	*ft_lnum_new_copy(t_longnumber *src);
t_longnumber	*ft_lnum_new_zero();
void			ft_lnum_destroy(t_longnumber **lnum);
int				ft_lnum_calc(t_longnumber *lnum, int pos);
#endif