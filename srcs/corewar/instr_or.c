/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/13 09:51:44 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES registered in the registers (1st and 2nd arg)
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	int		tmp;

	if (cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			&& cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			<= REG_NUMBER)
	{
		tmp = arg1 | arg2;
		proc->carry = (!tmp);
		regcpy(proc->regs[cor->arena[restricted_addr(proc->idx + proc->move
					+ 1)]], (void *)&tmp);
	}
}

static int	first_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg1;

	arg1 = 0;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) > REG_NUMBER || !arg1)
			*to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1 - 1]);
	}
	else if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx
					+ (get_int_arg_value(cor, (proc->idx + proc->move + 1)
					% MEM_SIZE, IND_BYTES)) % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE, D4_BYTES);
	return (arg1);
}

static int	second_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int arg2;

	arg2 = 0;
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[restricted_addr(proc->idx + proc->move + 1)])
				> REG_NUMBER || !arg2)
			*to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2 - 1]);
	}
	else if (type == IND_CODE)
		arg2 = get_int_arg_value(cor, (proc->idx
					+ (get_int_arg_value(cor, (proc->idx + proc->move + 1)
					% MEM_SIZE, IND_BYTES)) % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg2 = get_int_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE, D4_BYTES);
	return (arg2);
}

/*
** OR
** - opcode: 0x07
** - wait: 6
** - argcode: yes
** - args: REG/IND/DIR(4) REG/IND/DIR(4) REG
** - addressing retriction: yes
** - carry: 1 if the result of the '|' is 0, 0 otherwise
** - description: Stores the result of the bitwise '|' operation between the
**   first and second arguments in the register indicated by the third argument
*/

void		instr_or(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec
			&& (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	arg1 = first_arg(cor, proc, &to_exec, type);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec
			&& (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	arg2 = second_arg(cor, proc, &to_exec, type);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
