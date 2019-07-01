/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:28:38 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 16:28:11 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_flag(char *str, t_specs *specs)
{
	char	*ret;

	ret = str;
	if (specs->flags & FLAG_SPACE)
		ret = flag_space(str, specs);
	if (specs->flags & FLAG_OCTO)
		ret = flag_hash(str, specs);
	if (specs->flags & FLAG_PLUS)
		ret = flag_plus(str, specs);
	if (specs->flags & FLAG_ZERO)
		ret = flag_zero(str, specs);
	if (specs->flags & FLAG_MIN)
		ret = flag_minus(str, specs);
	return (ret);
}
