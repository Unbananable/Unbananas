/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/11 10:04:12 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg2 is a restricted address and the target of the instruction
*/

static void execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	proc->carry = (!arg1);
	memcpy_big(cor->arena + ((proc->idx + arg2) % MEM_SIZE), (void *)&arg1, REG_SIZE);
}

/*
** S (RG) S (RG | ID | D2) D (RG | D2)
** if D2, value is short
*/

void instr_sti(t_cor *cor, t_proc *proc)
{
	int type;
	t_bool to_exec;
	int arg1;
	int arg2;
	int arg3;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1]);
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2]);
		proc->move += byte_offset(type);
	}
	else
		proc->move += D2_BYTES;
	if (type == IND_CODE)
		arg2 = get_int_arg_value(cor, (proc->idx + get_int_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg2 = (int)get_short_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg3 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg3 = get_reg_value(proc->regs[arg3]);
		proc->move += byte_offset(type) + OPC_BYTE;
	}
	else if (type == DIR_CODE)
	{
		arg3 = (int)get_short_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
		proc->move += D2_BYTES + OPC_BYTE;
	}
	if (to_exec)
	{
		arg2 = (arg2 + arg3) % IDX_MOD;
		execute_instr(cor, proc, arg1, arg2);
	}
}
