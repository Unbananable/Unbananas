/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:47:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/25 15:26:09 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*converter(char *specs, va_list ap)
{
	char	*res;
	char	*res_nullchar;
	int		i;

	if (specs[ft_strlen(specs) - 1] == 'i')
		specs[ft_strlen(specs) - 1] = 'd';
	if (!specs[0]
			|| ft_strchr(" .lhzj+-0123456789#L", specs[ft_strlen(specs) - 1]))
		return (ft_strdup(""));
	res = parse_conv(ap, specs);
	res = parse_accufield(res, specs);
	res = parse_flag(res, specs);
	if (specs[ft_strlen(specs) - 1] == 'c' && ft_strstr(res, "^@"))
	{
		write(1, res, 1);
		if (!(res_nullchar = ft_strdup(res + 1)))
			exit_error("error: malloc failed\n", 2, res, specs);
		free(res);
		return (res_nullchar);
	}
	if (ft_strchr("dfi", specs[ft_strlen(specs) - 1]) && (i = -1))
		while (res[++i])
			if (res[i] == '\t')
				res[i] = ' ';
	return (res);
}

static t_form	init_struct(const char *format)
{
	t_form	fmt;

	fmt.i = 0;
	fmt.cnt = 0;
	fmt.str = format;
	return (fmt);
}

static t_form	write_color(t_form *fmt)
{
	char *color;

	if ((color = parse_color(fmt->str + fmt->i)))
	{
		fmt->cnt += fmt->i;
		if (!ft_strequ(color, "\033[0m"))
			write(1, color, 7);
		else
			write(1, color, 4);
		fmt->str += param_len(fmt->str + fmt->i) + fmt->i;
		fmt->i = 0;
	}
}

static void	write_arg(t_form *fmt, va_list ap)
{
	char	*specs;
	char	*arg;

	fmt->cnt += fmt->i;
	fmt->str += fmt->i + 1;
	fmt->i = 0;
	while (fmt->str[fmt->i] && (ft_strchr(" #+-.jhlzL", fmt->str[fmt->i])
			|| (fmt->str[fmt->i] >= '0' && fmt->str[fmt->i] <= '9')))
		fmt->i++;
	specs = ft_strsub(fmt->str, 0, fmt->i + 1);
	arg = converter(specs, ap);
	write(1, arg, ft_strlen(arg));
	if (fmt->str[0] &&
			ft_strchr(" .0123456789#+-jzhlL", *(fmt->str + fmt->i)))
		fmt->str += fmt->i;
	else if (fmt->str[0])
		fmt->str += fmt->i + 1;
	fmt->cnt += ft_strlen(arg);
	free(specs);
	free(arg);
	fmt->i = 0;
}

/*
** The main function is based on the fmt structure. While the format passed as
** an argument to the ft_printf function corresponds to a "normal"  string, the
** counter of the current character increases. If the counter is on a % or {
** character, it prints the begining of the strings, operates the necessary
** transformation (conversion or color), prints the results, and goes on the
** the same until the end of the format is reached.
*/

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_form		fmt;

	va_start(ap, format);
	fmt = init_struct(format);
	while (fmt.str[fmt.i])
	{
		if (fmt.str[fmt.i] == '{')
		{
			print_current(&fmt);
			write_color(&fmt);
		}
		else if (fmt.str[fmt.i] == '%')
		{
			print_current(&fmt);
			write_arg(&fmt, ap);
		}
		else
			fmt.i++;
	}
	write(1, fmt.str, fmt.i);
	va_end(ap);
	return (fmt.cnt + ft_strlen(fmt.str));
}
