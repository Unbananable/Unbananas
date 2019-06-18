/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:28:41 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/18 11:56:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	get_short_arg_value(t_cor *cor, int idx)
{
	return ((short)(cor->arena[restricted_addr(idx)] * 256
				+ cor->arena[restricted_addr(idx + 1)]));
}

int		get_int_arg_value(t_cor *cor, int idx, int size)
{
	int		res;
	int		i;

	res = cor->arena[restricted_addr(idx)];
	i = 0;
	while (++i < size)
		res = res * 256 + cor->arena[restricted_addr(idx + i)];
	return (res);
}
