/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/02 18:49:42 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_ld(t_cor cor, t_proc proc)
{
	if ((cor.arena[cyd_val(proc.idx + BYTE1)] != 0xd0
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != 0x90)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != 0xd0
				&& cor.arena[cyd_val(proc.idx + BYTES4)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != 0x90
				&& cor.arena[cyd_val(proc.idx + BYTES6)] > REG_NUMBER - 1))
		return (0);
	return (1);
}

/*
** First case: T_IND case
** Second case: T_DIR(4) case
*/

int		instr_ld(t_cor *cor, t_proc *proc)
{
	int		i;
	int		addr;

	i = -1;
	if (!arg_check_ld(&cor, &proc))
		return (0);
	if (cor->arena[cyd_val(proc->idx + BYTE1)] & 0b01000000)
	{
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->val + BYTES2 + i)];
		i = -1;
		addr = restricted_addr(proc->idx, ft_uchar_to_int_base(cor->hex, 16);
		ft_bzero(cor->hex, IND_SIZE);
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + addr + i)];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES4)], cor->hex);
		proc->move = BYTE1 + IND_SIZE + BYTE1 + BYTE1;
	}
	else
	{
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES2 + i)];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES6)], cor->hex);
		proc->move = BYTE1 + DIR_SIZE + BYTE1 + BYTE1;
	}
	proc->carry = (!ft_uchar_to_int_base(cor->hex, 16)) ? 1 : 0;
	ft_bzero(cor->hex, REG_SIZE);
	return (1);
}
