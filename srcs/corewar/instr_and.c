/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/02 15:02:53 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_and(t_cor cor, t_proc proc)
{
	if ((cor.arena[cyd_val(proc.idx + BYTE1)] != 0x54
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != 0xa4
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != 0xf4)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != 0x54
				&& (cor.arena[cyd_val(proc.idx + BYTE2)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE3)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE4)] > REG_NUMBER - 1))
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != 0xa4
				&& cor.arena[cyd_val(proc.idx + BYTES10)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != 0xf4
				&& cor.arena[cyd_val(proc.idx + BYTES6)] > REG_NUMBER - 1))
		return (0);
	return (1);
}

/*
** First case: T_REG/T_REG/T_REG
** Second case: T_DIR/T_DIR/T_REG
** Third case: T_IND/T_IND/T_REG
*/

int		instr_and(t_cor *cor, t_proc *proc)
{
	if (!arg_check_and(&cor, &proc))
		return (0);
}
