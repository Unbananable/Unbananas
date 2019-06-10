/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:51:11 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/08 16:29:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES extracted from the 1st and 2nd args
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	tmp;

	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] >= REG_NUMBER)
	{
		tmp = (int)arg1 + (int)arg2;
		tmp = (tmp < INT_MIN) ? INT_MIN : tmp;
		tmp = (tmp > INT_MAX) ? INT_MAX : tmp;
		proc->carry = (!tmp);
		ft_memcpy(proc->regs[cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]], tmp, REG_SIZE);
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
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1]);
	}
	else if (type == IND_CODE)
		arg1 = get_int_arg_val(cor, (proc->idx + get_int_arg_val(cor, (proc->idx + proc->move + 1) % MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_short_arg_val(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2]);
	}
	else if (type == DIR_CODE)
		arg2 = get_short_arg_val(cor, (proc->idx + proc->move + 1) % MEM_SIZE);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
