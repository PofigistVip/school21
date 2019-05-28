/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:29:18 by larlyne           #+#    #+#             */
/*   Updated: 2019/05/26 14:29:20 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int						pos;
	t_printf_arg			*arg;
	char					conv_type;
	char					length_mod;
	char					flags;
	int						width;
	int						width_pos;
	char					width_seted;
	int						precision;
	int						precision_pos;
	char					precision_seted;
	char					*raw_str;
	struct s_printf_elem	*next;
}				t_printf_elem;

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

t_printf_elem	*ft_parse(char *fmt, int *pos, int *ok);
t_printf_elem	*ft_parse_spec(char **fmt, int *pos, char *add, int *ok);
int				ft_parse_num_or_pos(int number, int *pos);
void			ft_parse_str_elem(t_printf_elem *el, char **fmt, char *ptr);
int				ft_parse_get_pos(char **fmt);
int				ft_len_cost(char len);
int				ft_parse_is_conv_spec(char c);
t_printf_elem	*ft_printf_elem_new(void);
char			ft_parse_len_mod(char **fmt);
char			ft_parse_flag(char **fmt);
int				ft_parse_get_number(char **str);
t_printf_elem	*ft_parse_rawstr(char **fmt, int *ok);
int				ft_parse_is_reference(char *str);
void			*ft_set_null_ok(int *ok);
void			*ft_set_ok_link(void *ret, int *ok);
int				ft_max_pos(t_printf_elem *els);
int				ft_process_pos(t_printf_elem *el, int pos, va_list *ap,
					t_printf_arg *arg);
void			ft_get_arg(char conv, char length, va_list *ap,
					t_printf_arg *arg);

t_printf_arg	*ft_arg_new(void);
t_printf_arg	*ft_get_args(t_printf_elem *els, va_list *ap, int end_pos,
					int *ok);
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
int				ft_display_p(int fd, t_printf_elem *el);
int				ft_display_big_c(int fd, t_printf_elem *el);
int				ft_display_big_s(int fd, t_printf_elem *el);
int				ft_display_f_big_f(int fd, t_printf_elem *el);
int				ft_display_unknown(int fd, t_printf_elem *el);

void			ft_memfree(t_printf_elem *els, t_printf_arg *args);

void			ft_get_sign_mantissa_fraction(long double val,
					t_double_keeper *keeper);
void			ft_f_round(t_lstr *int_p, t_lstr *dec_p, int precision);
int				ft_f_get_subnormal(__uint128_t fraction,
					t_lstr **int_p, t_lstr **dec_p);
int				ft_f_get_normal(int mant, __uint128_t fraction,
					t_lstr **int_p, t_lstr **dec_p);
t_lstr			*ft_get_decimal(int mant, __uint128_t fraction);
t_lstr			*ft_get_dec(int mant, __uint128_t fraction, int pos,
					int subnormal);
void			ft_temp_set(t_longnumber **temp, int mant);
int				ft_subnormal_count_zeroes(int one_pos);
int				ft_count_zeroes(int mantissa);
t_lstr			*ft_get_integer(int mant, __uint128_t fraction);
t_lstr			*ft_get_lnum(t_longnumber **lnum, t_longnumber **temp, int dec);
t_longnumber	*ft_lnum_pow5(int power);
t_longnumber	*ft_lnum_pow2(int power);

int				ft_lnum_dec(t_longnumber *lnum);
char			*ft_lnum_get_dec(t_longnumber *lnum);
char			*ft_lnum_get(t_longnumber *lnum);
void			ft_lnum_make_decimal(t_longnumber **lnum, int shift);
t_longnumber	*ft_lnum_pow(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b);
t_longnumber	*ft_lnum_mul(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b);
t_longnumber	*ft_lnum_mul_int(t_longnumber *a, int b, int dst_a);
t_longnumber	*ft_lnum_sub(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b);
t_longnumber	*ft_lnum_add(t_longnumber *a, t_longnumber *b,
					int dst_a, int dst_b);
int				ft_lnum_length(t_longnumber *lnum);
t_longnumber	*ft_lnum_new_int(int number);
t_longnumber	*ft_lnum_new_copy(t_longnumber *src);
t_longnumber	*ft_lnum_new_zero();
void			ft_lnum_destroy(t_longnumber **lnum);
int				ft_lnum_calc(t_longnumber *lnum, int pos);
#endif
