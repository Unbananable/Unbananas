/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:28:38 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/26 12:39:43 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_flag(char *str, t_specs specs)
{
	if (specs.flags & FLAG_SPACE)
		str = flag_space(str, specs.conv);
	if (specs.flags & FLAG_OCTO)
		str = flag_hash(str, specs.conv);
	if (specs.flags & FLAG_PLUS)
		str = flag_plus(str, specs.conv);
	if (specs.flags & FLAG_ZERO)
		str = flag_zero(str, specs.conv);
	if (specs.flags & FLAG_MIN)
		str = flag_minus(str, specs.conv);
	return (str);
}
