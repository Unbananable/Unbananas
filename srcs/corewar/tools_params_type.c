/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_params_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:34:05 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/10 12:31:47 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int bit_offset(int param_idx)
{
	return (BYTE_SIZE - param_idx * 2 * BIT);
}

int bits_peer_type(t_cor *cor, t_proc *proc, int param_idx)
{
	int bit1;
	int bit2;
	int res;

	bit1 = (cor->arena[(proc->idx + ARGC_BYTE) % MEM_SIZE] >> (bit_offset(param_idx) + 1)) & 1;
	bit2 = (cor->arena[(proc->idx + ARGC_BYTE) % MEM_SIZE] >> bit_offset(param_idx)) & 1;
	if (bit1)
		res = (bit2) ? IND_CODE : DIR_CODE;
	else
		res = (bit2) ? REG_CODE : NULL_CODE;
	return (res);
}

int byte_offset(int param_type)
{
	if (param_type == REG_CODE)
		return (REG_BYTE);
	if (param_type == DIR_CODE)
		return (D4_BYTES);
	if (param_type == IND_CODE)
		return (IND_BYTES);
	if (param_type == NULL_CODE)
		return (0);
	return (0);
}

