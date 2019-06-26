/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_accufield.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:35:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/26 12:24:00 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*parse_accufield(char *str, t_specs specs)
{
	int		len;

	len = 0;
	if (specs.flags & ACCURACY)
		if (!(str = accuracy(str, specs)))
			exit_error("error: malloc failed\n", 1, specs);
	if (specs.flags & FIELD_WIDTH)
		if (!(str = field_width(str, specs)))
			exit_error("error: malloc failed\n", 2, str, specs);
	return (str);
}
