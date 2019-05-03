/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 17:09:03 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	sum;
	char	*res;

	sum = ft_uchar_to_int_base(proc->regs[arg1], 16)
		+ ft_uchar_to_int_base(proc->regs[arg2], 16);
	sum = (sum < INT_MIN) ? INT_MIN : sum;
	sum = (sum > INT_MAX) ? INT_MAX : sum;
	if (!(res = ft_int_to_uchar((int)sum)))
		error(cor, "Failed to ft_itoa in instr_add");
	fill_register(cor, cor->arena[(proc->idx + proc->move) % MEM_SIZE], res);
	free(res);
	proc->carry = (!sum) ? 1 : 0;
}

/*
** Takes 3 T_REG as parameters
*/

int			instr_add(t_cor *cor, t_proc *proc)
{
	int		type;
	int		to_exec;
	int		arg1;
	int		arg2;

	to_exec = 1;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	arg1 = cor->arena[cyd_val(proc->idx + proc->move)];
	proc->move += REG_BYTE;
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	arg2 = cor->arena[cyd_val(proc->idx + proc->move)];
	proc->move += REG_BYTE;
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
}

static void	execute_instr(t_cor *cor, t_proc *proc)
{

}

/*
** First case: T_REG/T_REG/T_REG
** Second case: T_DIR/T_DIR/T_REG
** Third case: T_IND/T_IND/T_REG
*/

int			instr_and(t_cor *cor, t_proc *proc)
{
	int		type;
	int		to_exec;

	to_exec = 1;
	proc->move = ARGC_BYTE;
}









static int	arg_check_and(t_cor cor, t_proc proc)
{
	if ((cor.arena[cyd_val(proc.idx + BYTE1)] != RGRGRG
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != DIDIRG
			&& cor.arena[cyd_val(proc.idx + BYTE1)] != IDIDRG)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == RGRGRG
				&& (cor.arena[cyd_val(proc.idx + BYTE2)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE3)] > REG_NUMBER - 1
					|| cor.arena[cyd_val(proc.idx + BYTE4)] > REG_NUMBER - 1))
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == DIDIRG
				&& cor.arena[cyd_val(proc.idx + BYTES10)] > REG_NUMBER - 1)
			|| (cor.arena[cyd_val(proc.idx + BYTE1)] == IDIDRG
				&& cor.arena[cyd_val(proc.idx + BYTES6)] > REG_NUMBER - 1))
		return (0);
	return (1);
}


int		instr_and(t_cor *cor, t_proc *proc)
{
	int		i;
	int		arg1;
	int		arg2;
	char	*res;

	if (!arg_check_and(*cor, *proc))
		return (0);
	i = -1;
	if (cor->arena[cyd_val(proc->idx + BYTE1)] != RGRGRG)
	{
		while (++i < REG_SIZE)
			cor->hex[i] = proc->regs[cor->arena[cyd_val(proc->idx + BYTES2)]][i]
				& proc->regs[cor->arena[cyd_val(proc->idx + BYTES3)]][i];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES4)], cor->hex);
		proc->carry = (!ft_uchar_to_int_base(cor->hex, 16)) ? 1 : 0;
		proc->move = BYTE1 + 3 * BYTE1 + BYTE1;
	}
	else if (cor->arena[cyd_val(proc->idx + BYTE1)] != DIDIRG)
	{
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + BYTES2 + i)];
		arg1 = ft_uchar_to_int_base(cor->hex, 16);
		i = -1;
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + BYTES6 + i)];
		arg2 = ft_uchar_to_int_base(cor->hex, 16);
		res = ft_int_to_uchar(arg1 & arg2);
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES10)], res);
		proc->carry = (arg1 & arg2 == 0) ? 1 : 0;
		free(res);
		proc->move = BYTE1 + 2 * DIR_SIZE + BYTE1 + BYTE1;
	}
	else
	{
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES2 + i)];
		arg1 = ft_uchar_to_int_base(cor->hex, 16);
		i = -1;
		while (++i < IND_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc->idx + BYTES4 + i)];
		arg2 = ft_uchar_to_int_base(cor->hex, 16);
		addr = restricted_addr(proc->idx, arg1 & arg2);
		i = -1;
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(addr + i)];
		fill_register(cor, cor->arena[cyd_val(proc->idx + BYTES6)], cor->hex);
		proc->carry = (!ft_uchar_to_int_base(cor->hex, 16)) ? 1 : 0;
		proc->move = BYTE1 + 2 * IND_SIZE + BYTE1 + BYTE1;
	}
	ft_bzero(cor->hex, REG_SIZE);
	return (1);
}
