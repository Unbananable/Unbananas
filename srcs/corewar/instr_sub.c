/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/02 14:48:40 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_sub(t_cor cor, t_proc proc)
{
	if (cor.arena[cyd_val(proc.idx + BYTES2)] > REG_NUMBER - 1
			|| cor.arena[cyd_val(proc.idx + BYTES3)] > REG_NUMBER - 1
			|| cor.arena[cyd_val(proc.idx + BYTES4)] > REG_NUMBER - 1
			|| cor.arena[cyd_val(proc.idx + BYTES1)] != 0x54)
		return (0);
	return (1);
}

/*
** Takes 3 T_REG as parameters
*/

int	instr_add(t_cor *cor, t_proc *proc)
{
	int		r1;
	int		r2;
	char	*res;
	long	sum;

	if (!arg_check_sub(&cor, &proc))
		return (0);
	r1 = cor->arena[cyd_val(proc->idx + BYTES2)];
	r2 = cor->arena[cyd_val(proc->idx + BYTES3)];
	sum = ft_atoi_base(proc->regs[r1], 16) - ft_atoi_base(proc->regs[r2], 16);
	if (sum < INT_MIN || sum > INT_MAX)
		return (0);
	if (!(res = ft_itoa((int)sum)))
		return (0);
	fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES4)], res);
	free(res);
	proc->carry = (!sum) ? 1 : 0;
	proc->move = BYTES5;
	return (1);
}
