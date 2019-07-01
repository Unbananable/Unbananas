/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:26:32 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/25 16:06:35 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	flag_sanitize (t_specs *specs)
{
	if ((ft_strchr("diouxX", specs->conv) && specs->flags & ACCURACY)
			|| specs->flags & FLAG_MIN)
		if (specs->flags & FLAG_ZERO)
			specs->flags = specs->flags ^ FLAG_ZERO;
	if (specs->flags & FLAG_PLUS)
		if (specs->flags & FLAG_SPACE)
			specs->flags = specs->flags ^ FLAG_SPACE;
}

static void add_flag(t_form *fmt, t_specs *specs) // [TO DO] Cas ou les flags sont répétés [TO DO] Cas d'un flag invalide [TO DO] Cas de plusieurs modifiers
{
	if (fmt->str[fmt->i] == ' ')
		specs->flags = specs->flags | FLAG_SPACE;
	else if (fmt->str[fmt->i] == '#')
		specs->flags = specs->flags | FLAG_OCTO;
	else if (fmt->str[fmt->i] == '+')
		specs->flags = specs->flags | FLAG_PLUS;
	else if (fmt->str[fmt->i] == '-')
		specs->flags = specs->flags | FLAG_MIN;
	else if (fmt->str[fmt->i] == '0')
		specs->flags = specs->flags | FLAG_ZERO;
	else if (fmt->str[fmt->i] == 'l')
	{
		if (fmt->str[fmt->i + 1] == 'l')
		{
			specs->mod = specs->mod | MOD_LL;
			fmt->i++;
		}
		else
			specs->mod = specs->mod | MOD_L;
	}
	else if (fmt->str[fmt->i] == 'j')
		specs->mod = specs->mod | MOD_J;
	else if (fmt->str[fmt->i] == 'z')
		specs->mod = specs->mod | MOD_Z;
	else if (fmt->str[fmt->i] == 'L')
		specs->mod = specs->mod | MOD_BIG_L;
	else if (fmt->str[fmt->i] == 'h')
	{
		if (fmt->str[fmt->i + 1] == 'h')
		{
			specs->mod = specs->mod | MOD_HH;
			fmt->i++;
		}
		else
			specs->mod = specs->mod | MOD_H;
	}
	else if (fmt->str[fmt->i] >= '1' && fmt->str[fmt->i] <= '9')
	{
		specs->flags = specs->flags | FIELD_WIDTH;
		while (fmt->str[fmt->i] >= '0' && fmt->str[fmt->i] <= '9')
		{
			specs->field_width = specs->field_width * 10 + fmt->str[fmt->i] - '0';
			fmt->i++;
		}
		fmt->i--;
	}
	else if (fmt->str[fmt->i] == '.')
	{
		specs->flags = specs->flags | ACCURACY;
		fmt->i++;
		while (fmt->str[fmt->i] >= '1' && fmt->str[fmt->i] <= '9')
		{
			specs->accuracy = specs->accuracy * 10 + fmt->str[fmt->i] - '0';
			fmt->i++;
		}
		fmt->i--;
	}
	else
		fmt->i--;
	fmt->i++;
}

static int  is_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o'
			|| c == 'u' || c == 'x' || c == '%' || c == 'f')
		return (1);
	return (0);
}

static void  set_conv_specs(t_form *fmt, t_specs *specs)
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

void	write_arg(t_form *fmt, va_list ap)
{
	char	*res;
	t_specs	specs;

	fmt->i++;
	set_conv_specs(fmt, &specs);
/*printf("========= SPECS =========\n");
printf("FW  .  0  +  -  # SP\n");
char i = 1 << 6;
while (i)
{
printf("%2d ", i & specs.flags);
i >>= 1;
}
printf("\n");
printf("========= MODS  =========\n");
printf("ll  L  l  z  j hh  h\n");
i = 1 << 6;
while (i)
{
printf("%2d ", i & specs.mod);
i >>= 1;
}
printf("\n");
printf("conv = %c\n", specs.conv);
printf("accuracy = %d\n", specs.accuracy);
printf("field_width = %d\n", specs.field_width);*/
	res = converter(&specs, ap);
//printf("null_char = %d\n", specs.null_char);
//printf("res = %s\n", res);
	write(1, res, specs.len);
	fmt->cnt += specs.len;
	free(res);
	res = NULL;
	fmt->i = 0;
}