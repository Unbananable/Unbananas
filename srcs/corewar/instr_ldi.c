/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:27:40 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 12:26:38 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	arg_check_ldi(t_cor cor, t_proc proc)
{
	if ((cor.arena[cyd_val(proc.idx + BYTE1)] != DIDIRG
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != IDDIRG
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != RGDIRG
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != DIRGRG
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != IDRGRG
				&& cor.arena[cyd_val(proc.idx + BYTE1)] != RGRGRG)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == DIDIRG
				&& cor.arena[cyd_val(proc.idx + BYTES6)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == IDDIRG
				&& cor.arena[cyd_val(proc.idx + BYTES6)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == RGDIRG
				&& cor.arena[cyd_val(proc.idx + BYTES2)] > REG_NUMBER - 1
				&& cor.arena[cyd_val(proc.idx + BYTES5)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == DIRGRG
				&& cor.arena[cyd_val(proc.idx + BYTES4)] > REG_NUMBER - 1
				&& cor.arena[cyd_val(proc.idx + BYTES5)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == IDRGRG
				&& cor.arena[cyd_val(proc.idx + BYTES4)] > REG_NUMBER - 1
				&& cor.arena[cyd_val(proc.idx + BYTES5)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == RGRGRG
				&& cor.arena[cyd_val(proc.idx + BYTES2)] > REG_NUMBER - 1
				&& cor.arena[cyd_val(proc.idx + BYTES3)] > REG_NUMBER - 1
				&& cor.arena[cyd_val(proc.idx + BYTES4)] > REG_NUMBER - 1)
		return (0);
	return (1);
}

/*
** First case: T_DIR(2)/T_DIR(2)/T_REG
** Second case: T_IND/T_DIR(2)/T_REG
** Third case: T_REG/T_DIR(2)/T_REG
** Fourth case: T_DIR(2)/T_REG/T_REG
** Fifth case: T_IND/T_REG/T_REG
** Sixth case: T_REG/T_REG/T_REG
*/

int		instr_ldi(t_cor *cor, t_proc *proc)
{
	int		i;
	int		addr;
	int		arg1;
	int		arg2;
	long	sum;

	i = -1;
	if (!arg_check_ldi(*cor, *proc))
		return (0);
	if (cor->arena[cyd_val(proc->idx + BYTE1)] == DIDIRG)
	{
		while (++i < DIR_SIZE / 2)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES2 + i)];
		arg1 = ft_uchar_to_int_base(cor->hex, 16);
		ft_bzero(cor->hex, DIR_SIZE / 2);
		i = -1;
		while (++i < DIR_SIZE / 2)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES4 + i)];
		ft_bzero(cor->hex, DIR_SIZE / 2);
		arg2 = ft_uchar_to_int_base(cor->hex, 16);
		sum = (arg1 + arg2 < SHRT_MIN) ? SHRT_MIN : arg1 + arg2;
		sum = (arg1 + arg2 > SHRT_MAX) ? SHRT_MAX : arg1 + arg2;
		addr = restricted_addr(proc->idx, sum);
		i = -1;
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + addr + i)];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES6)], cor->hex);
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] == IDDIRG)
	{
		
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] == RGDIRG)
	{
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] == DIRGRG)
	{
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] == IDRGRG)
	{
	}
	else //case RGRGRG
	{
	}
	//move
	//bzero hex
	//carry
	return (1);
}
