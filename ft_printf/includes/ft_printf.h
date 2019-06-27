/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:15:45 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/27 13:52:27 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <wchar.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# define UINT_MAX  4294967295

# define FLAG_SPACE 1
# define FLAG_OCTO 2
# define FLAG_MIN 4
# define FLAG_PLUS 8
# define FLAG_ZERO 16
# define ACCURACY 32
# define FIELD_WIDTH 64

# define MOD_H 1
# define MOD_HH 2
# define MOD_J 4
# define MOD_Z 8
# define MOD_L 16
# define MOD_BIG_L 32
# define MOD_LL 64

typedef va_list	t_va;

typedef struct	s_specs
{
	int				flags;
	int				mod;
	unsigned int	field_width;
	unsigned int	accuracy;
	char			conv;
}				t_specs;

typedef struct	s_conv
{
	char	conv;
	char	*(*f)(t_va, t_specs);
}				t_conv;

typedef struct	s_flag
{
	char	c;
	char	*(*f)(char *, char);
}				t_flag;

/*
** FORMAT STRUCTURE
** - fmt: format to print;
** - cnt: total length of the format
** - i: current read character
*/

typedef struct	s_form
{
	int			i;
	int			cnt;
	const char	*str;
}				t_form;

int				ft_printf(const char *format, ...);
int				param_len(const char *format);
char			*parse_color(const char *format);
char			*parse_flag(char *str, t_specs specs);
char			*parse_accufield(char *str, t_specs specs);
char			*parse_conv(va_list ap, t_specs specs);
char			*conv_d(va_list ap, t_specs specs);
char			*conv_i(va_list ap, t_specs specs);
char			*conv_o(va_list ap, t_specs specs);
char			*conv_u(va_list ap, t_specs specs);
char			*conv_x(va_list ap, t_specs specs);
char			*conv_big_x(va_list ap, t_specs specs);
char			*conv_f(va_list ap, t_specs specs);
char			*conv_c(va_list ap, t_specs specs);
char			*conv_s(va_list ap, t_specs specs);
char			*conv_p(va_list ap, t_specs specs);
char			*conv_binary(va_list ap, t_specs specs);
char			*conv_percentage(va_list ap, t_specs specs);
char			*flag_plus(char *str, char c);
char			*flag_minus(char *str, char c);
char			*flag_space(char *str, char c);
char			*flag_hash(char *str, char c);
char			*flag_zero(char *str, char c);
char			*accuracy(char *str, t_specs specs);
char			*field_width(char *str, t_specs specs);
void			exit_error(char *er_mess, int nbfree, ...);
int				move_right(char *str, int nbchar, char c);
char			*suffix(char *suf, char *str);
char			*parse_color(const char *format);
int				param_len(const char *format);
unsigned char	*concatenate(unsigned char *s1, unsigned char *s2);
char			*conv_longf(va_list ap, t_specs specs);
void			print_current(t_form *fmt);
void			write_arg(t_form *fmt, va_list ap);
char			*converter(t_specs specs, va_list ap);

#endif
