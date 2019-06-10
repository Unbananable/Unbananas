/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:28:41 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/08 15:34:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	get_short_arg_value(t_cor *cor, int idx)
{
	return ((short)(cor->arena[idx] * 256 + cor->arena[idx + 1]));
}

int		get_int_arg_value(t_cor *cor, int idx, int size)
{
	int		res;
	int		i;

	res = cor->arena[idx];
	i = 0;
	while (++i < size)
		res = res * 256 + cor->arena[idx + i];
	return (res);
}
