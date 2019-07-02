/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:26:32 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/02 14:07:28 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_sanitize(t_specs *specs)
{
	if ((ft_strchr("diouxX", specs->conv) && specs->flags & ACCURACY)
			|| specs->flags & FLAG_MIN)
		if (specs->flags & FLAG_ZERO)
			specs->flags = specs->flags ^ FLAG_ZERO;
	if (specs->flags & FLAG_PLUS)
		if (specs->flags & FLAG_SPACE)
			specs->flags = specs->flags ^ FLAG_SPACE;
}

static int	is_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
			|| c == 'u' || c == 'x' || c == '%' || c == 'f')
		return (1);
	return (0);
}

static void	set_conv_specs(t_form *fmt, t_specs *specs)
{
	specs->flags = 0;
	specs->mod = 0;
	specs->accuracy = 0;
	specs->field_width = 0;
	specs->null_char = 0;
	specs->len = 0;
	while (fmt->str[fmt->i] && !is_conv(fmt->str[fmt->i]))
		add_flag(fmt, specs);
	specs->conv = (fmt->str[fmt->i] == 'i') ? 'd' : fmt->str[fmt->i];
	flag_sanitize(specs);
	//[TO DO] Gérer le cas ou il n'y a pas de conversion
	fmt->str += fmt->i + 1;
	fmt->i = 0;
}

void		write_arg(t_form *fmt, va_list ap)
{
	char	*res;
	t_specs	specs;

	fmt->i++;
	set_conv_specs(fmt, &specs);
	res = converter(&specs, ap);
	write(1, res, specs.len);
	fmt->cnt += specs.len;
	free(res);
	res = NULL;
	fmt->i = 0;
}
