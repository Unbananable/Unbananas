/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 11:44:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_st(t_cor cor, t_proc proc)
{
	if (cor.arena[cyd_val(proc.idx + BYTES2)] > REG_NUMBER - 1
		|| (cor.arena[cyd_val(proc.idx + BYTE1)] != RGRGNN
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != RGIDNN)
		|| (cor.arena[cyd_val(proc.idx + BYTE1)] == RGRGNN
			&& cor.arena[cyd_val(proc.idx + BYTES3)] > REG_NUMBER - 1))
		return (0);
	return (1);
}

/*
** First case: T_REG case
** Second case: T_IND case
*/

int		instr_st(t_cor *cor, t_proc *proc)
{
	int		i;
	int		addr;

	if (!arg_check_st(*cor, *proc))
		return (0);
	i = -1;
	if (cor->arena[cyd_val(proc->idx + BYTE1)] & 0b00100000)
	{
		while (++i < REG_SIZE)
			proc->regs[cor->arena[cyd_val(proc->idx + BYTES3)]
				- 1][i] = proc->regs[cor->arena[cyd_val(proc->idx
						+ BYTES2)] - 1][i];
		proc->move = BYTE1 + 2 * BYTE1 + BYTE1;
	}
	else
	{
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES3 + i)];
		addr = restricted_addr(proc->idx, ft_atos_base(cor->hex, 16));
		ft_bzero(cor->hex, IND_SIZE);
		i = -1;
		while (++i < REG_SIZE)
			cor->arena[cyd_val(addr
					+ i)] = proc->regs[cor->arena[cyd_val(proc->idx
						+ BYTES2)]][i];
		proc->move = BYTE1 + BYTE1 + IND_SIZE + BYTE1;
	}
	return (1);
}
