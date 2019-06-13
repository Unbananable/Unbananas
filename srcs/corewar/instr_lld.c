/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/13 09:49:15 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 is the int VALUE to store into arg2 (the targeted register number)
*/

static void	execute_instr(t_proc *proc, int arg1, int arg2)
{
	proc->carry = (!arg1);
	regcpy(proc->regs[arg2 - 1], (void *)&arg1);
}

/*
** LONG DIRECT LOAD
** - opcode: 0x0D
** - wait: 10
** - argcode: yes
** - args: IND/DIR(4) REG
** - adressing restriction: no
** - carry: 1 if the first argument is 0, 0 otherwise
** - description: Loads the value of the first argument in the register
**   indicated by the second argument.
*/

void		instr_lld(t_cor *cor, t_proc *proc)
{
	t_bool	to_exec;
	int		type;
	int		arg1;
	int		arg2;

	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (type == IND_CODE || type == DIR_CODE);
	if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx
					+ get_int_arg_value(cor, (proc->idx + proc->move + 1)
						% MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx
					+ proc->move + 1) % MEM_SIZE, D4_BYTES);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if ((arg2 = cor->arena[restricted_addr(proc->idx + proc->move + 1)])
			> REG_NUMBER || !arg2)
		to_exec = false;
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(proc, arg1, arg2);
	proc->move += OPC_BYTE;
}
