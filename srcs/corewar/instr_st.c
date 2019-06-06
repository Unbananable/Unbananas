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

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	char	*res;

	if ()
}

/*
** S (RG) D (RG | ID)
** if ID, value is short
*/

void		instr_st(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg1 = ft_uchar_to_int_base(proc->regs[arg1], 16);
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE));
	if (type == IND_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + (ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move + 1, IND_BYTES), 16) % IDX_MOD), REG_SIZE), 16);
	else if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg2 = ft_uchar_to_int_base(proc->regs[arg2], 16);
	}
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}

/* *************************************************************************** */

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
