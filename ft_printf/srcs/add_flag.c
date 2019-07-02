/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:16:53 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/02 14:02:26 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_mod(t_form *fmt, t_specs *specs)
{
	if (fmt->str[fmt->i] == 'l')
	{
		specs->mod = (fmt->str[fmt->i + 1] == 'l') ? specs->mod | MOD_LL
				: specs->mod | MOD_L;
		if (fmt->str[fmt->i + 1] == 'l')
			fmt->i++;
	}
	else if (fmt->str[fmt->i] == 'j')
		specs->mod = specs->mod | MOD_J;
	else if (fmt->str[fmt->i] == 'z')
		specs->mod = specs->mod | MOD_Z;
	else if (fmt->str[fmt->i] == 'L')
		specs->mod = specs->mod | MOD_BIG_L;
	else if (fmt->str[fmt->i] == 'h')
	{
		specs->mod = (fmt->str[fmt->i + 1] == 'h') ? specs->mod | MOD_HH
				: specs->mod | MOD_H;
		if (fmt->str[fmt->i + 1] == 'h')
			fmt->i++;
	}
}

static void	add_accufield(t_form *fmt, t_specs *specs)
{
	if (fmt->str[fmt->i] >= '1' && fmt->str[fmt->i] <= '9')
	{
		specs->flags = specs->flags | FIELD_WIDTH;
		while (fmt->str[fmt->i] >= '0' && fmt->str[fmt->i] <= '9')
		{
			specs->field_width = specs->field_width * 10
					+ fmt->str[fmt->i] - '0';
			fmt->i++;
		}
		fmt->i--;
	}
	else if (fmt->str[fmt->i] == '.')
	{
		specs->flags = specs->flags | ACCURACY;
		fmt->i++;
		while (fmt->str[fmt->i] >= '0' && fmt->str[fmt->i] <= '9')
		{
			specs->accuracy = specs->accuracy * 10 + fmt->str[fmt->i] - '0';
			fmt->i++;
		}
		fmt->i--;
	}
}

static int	is_mod(char c)
{
	if (c == 'l' || c == 'L' || c == 'h' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

void		add_flag(t_form *fmt, t_specs *specs) // [TO DO] Cas ou les flags sont répétés [TO DO] Cas d'un flag invalide [TO DO] Cas de plusieurs modifiers
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
	else if (is_mod(fmt->str[fmt->i]))
		add_mod(fmt, specs);
	else if (ft_isdigit(fmt->str[fmt->i]) || fmt->str[fmt->i] == '.')
		add_accufield(fmt, specs);
	else
		fmt->i--;
	fmt->i++;
}
