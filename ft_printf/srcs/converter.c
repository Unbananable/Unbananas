/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:47:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/26 12:24:14 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*converter(t_specs specs, va_list ap)
{
	char	*res;
	char	*res_nullchar;
	int		i;

	res = parse_conv(ap, specs);
	res = parse_accufield(res, specs);
	res = parse_flag(res, specs);
	return (res);
}