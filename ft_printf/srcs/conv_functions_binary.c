/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions_binary.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:53:33 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/26 11:36:09 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*conv_binary(va_list ap, t_specs specs)
{
	char				*str;
	unsigned long long	z;
	int					size;
	int					i;
	unsigned long long	x;

	(void)specs;
	x = va_arg(ap, unsigned long long);
	if (x > UINT_MAX)
		size = 64;
	else
		size = 32;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		exit_error("malloc failed", 0);
	str[size] = 0;
	z = 1 << (size - 1);
	i = -1;
	while (++i < size)
	{
		str[i] = (x & z) ? '1' : '0';
		z >>= 1;
	}
	return (str);
}
