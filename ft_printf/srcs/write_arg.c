/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:26:32 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/25 16:06:35 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void add_flag(t_form *fmt, t_arg *arg) // [TO DO] Cas ou les flags sont répétés
{
    if (fmt->str[fmt->i] == ' ')
        arg->flags = arg->flags | FLAG_SPACE;
    else if (fmt->str[fmt->i] == '#')
        arg->flags = arg->flags | FLAG_OCTO;
    else if (fmt->str[fmt->i] == '+')
        arg->flags = arg->flags | FLAG_PLUS;
    else if (fmt->str[fmt->i] == '-')
        arg->flags = arg->flags | FLAG_MIN;
    else if (fmt->str[fmt->i] == '0')
        arg->flags = arg->flags | FLAG_ZERO;
    else if (fmt->str[fmt->i] >= '1' && fmt->str[fmt->i] <= '9')
    {
        arg->flags = arg->flags | FIELD_WIDTH;
        arg->field_width = fmt->str[fmt->i] - '0';
        while (fmt->str[++fmt->i] >= '1' && fmt->str[++fmt->i] <= '9')
            arg->field_width = arg->field_width * 10 + fmt->str[fmt->i] - '0';
        fmt->i--;
    }
    else if (fmt->str[fmt->i] == '.')
    {
        arg->flags = arg->flags | ACCURACY;
        arg->accuracy = 0;
        while (fmt->str[++fmt->i] >= '1' && fmt->str[++fmt->i] <= '9')
            arg->field_width = arg->field_width * 10 + fmt->str[fmt->i] - '0';
        fmt->i--;
    }
    else
        fmt->i--;
    fmt->i++;
    
}

static int  is_conv(char c)
{
    if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
            || c == 'u' || c == 'x' || c == '%')
        return (1);
    return (0);
}

static int  set_conv_characteristics(t_form *fmt, t_arg *arg)
{
    arg->flags = 0;
    while (fmt->str[fmt->i] && !is_conv(fmt->str[fmt->i]))
        add_flag(fmt, arg);
    arg->conv = fmt->str[fmt->i];
    //[TO DO] Gérer le cas ou il n'y a pas de conversion
    fmt->str += fmt->i;
    fmt->i = 0;
}

void	write_arg(t_form *fmt, va_list ap)
{
	char	*res;
    t_arg   arg;

    fmt->i++;
	set_conv_characteristics(fmt, &arg);
	res = converter(arg, ap);
	write(1, res, ft_strlen(res));
	fmt->cnt += ft_strlen(res);
	free(res);
	fmt->i = 0;
}