/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/02 17:19:19 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_and(t_cor cor, t_proc proc)
{
	if ((cor.arena[cyd_val(proc.idx + BYTE1)] != RGRGRG
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != D4D4RG
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != IDIDRG)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != RGRGRG
				&& (cor.arena[cyd_val(proc.idx + BYTE2)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE3)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE4)] > REG_NUMBER - 1))
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != D4D4RG
				&& cor.arena[cyd_val(proc.idx + BYTES10)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] != IDIDRG
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
	int		i;
	int		arg1;
	int		arg2;
	char	*res;

	if (!arg_check_and(&cor, &proc))
		return (0);
	i = -1;
	if (cor->arena[cyd_val(proc->idx + BYTE1)] != RGRGRG)
	{
		while (++i < REG_SIZE)
			cor->hex[i] = proc->regs[cor->arena[cyd_val(proc->idx + BYTES2)]][i]
				& proc->regs[cor->arena[cyd_val(proc->idx + BYTES3)]][i];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES4)], cor->hex);
		proc->move = BYTES5;
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] != D4D4RG)
	{
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + BYTES2 + i)];
		arg1 = ft_atoi_base(cor->hex, 16);
		i = -1;
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + BYTES6 + i)];
		arg2 = ft_atoi_base(cor->hex, 16);
		res = ft_itoa(arg1 & arg2);
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES10)], res);
		free(res);
		proc->move = BYTES11;
	}
	else
	{
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES2 + i)];
		arg1 = ft_atoi_base(cor->hex, 16);
		i = -1;
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES4 + i)];
		arg2 = ft_atoi_base(cor->hex, 16);
		addr = restricted_addr(proc->idx, arg1 & arg2);
		i = -1;
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(addr + i)];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES6)], cor->hex);
		proc->move = BYTES7;
	}
	ft_bzero(cor->hex, REG_SIZE);
	return (1);
}
