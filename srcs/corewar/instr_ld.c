/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/11 14:08:33 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 is the int VALUE to store into arg2 (the targeted register number)
*/

static void execute_instr(t_proc *proc, int arg1, int arg2)
{
	proc->carry= (!arg1);
	regcpy(proc->regs[arg2 - 1], (void *)&arg1);
}

/*
** S (ID/D4) D (RG)
*/

void instr_ld(t_cor *cor, t_proc *proc)
{
	t_bool to_exec;
	int type;
	int arg1;
	int arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && (type == IND_CODE || type == DIR_CODE));
	if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx + (get_int_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE, IND_BYTES) % IDX_MOD)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE, D4_BYTES);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if ((arg2 = cor->arena[restricted_addr(proc->idx + proc->move + 1)]) > REG_NUMBER || !arg2)
		to_exec = false;
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(proc, arg1, arg2);
	proc->move += OPC_BYTE;
}
