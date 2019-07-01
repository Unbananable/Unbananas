/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_accufield.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:35:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 15:27:54 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*parse_accufield(char *str, t_specs *specs)
{
	int		len;

	len = 0;
	if (specs->flags & ACCURACY)
	{
		if (!(str = accuracy(str, specs)))
			exit_error("error: malloc failed\n", 1, specs);
	}
	if (specs->flags & FIELD_WIDTH)
	{
		if (!(str = field_width(str, specs)))
			exit_error("error: malloc failed\n", 2, str, specs);
	}
	return (str);
}
