/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_params_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:34:05 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 16:49:25 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	byte_offset(int param_idx)
{
	return (BYTE_SIZE - param_idx * 2 * BIT);
}

int			type_bits_peer(t_cor *cor, t_proc *proc, int param_idx)
{
	int		bit1;
	int		bit2;
	int		res

	bit1 = (cor->arena[cyd_val(proc->idx
				+ BYTE1)] >> (byte_offset(param_idx) + 1)) & 1;
	bit2 = (cor->arena[cyd_val(proc->idx
				+ BYTE1)] >> byte_offset(param_idx)) & 1;
	if (bit1)
		res = (bit2) ? IND_CODE : DIR_CODE;
	else
		res = (bit2) ? REG_CODE : NULL_CODE;
	return (res);
}
