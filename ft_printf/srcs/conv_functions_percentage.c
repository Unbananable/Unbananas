/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions_percentage.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 09:57:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/27 14:08:15 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*conv_percentage(va_list ap, t_specs specs)
{
	ap += 0;
	(void)specs;
	return (ft_strdup("%"));
}
