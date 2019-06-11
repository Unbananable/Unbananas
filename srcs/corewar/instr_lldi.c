/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:51:11 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/11 10:10:17 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES extracted from the 1st and 2nd args
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	tmp;

	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] && cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		tmp = (int)arg1 + (int)arg2;
		tmp = (tmp < INT_MIN) ? INT_MIN : tmp;
		tmp = (tmp > INT_MAX) ? INT_MAX : tmp;
		proc->carry = (!tmp);
		memcpy_big(proc->regs[cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] - 1], (void *)&tmp, REG_SIZE);
	}
}

/*
** S (RG | ID | D2) S (RG | D2) D (RG)
*/

void		instr_lldi(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) > REG_NUMBER || !arg1)
			to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1 - 1]);
		proc->move += byte_offset(type);
	}
	else
		proc->move += D2_BYTES;
	if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx + get_int_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_short_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) > REG_NUMBER || !arg2)
			to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2 - 1]);
		proc->move += byte_offset(type);
	}
	else if (type == DIR_CODE)
	{
		arg2 = get_short_arg_value(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
		proc->move += D2_BYTES;
	}
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
