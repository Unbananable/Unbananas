/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_xor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:33:09 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES registered in the registers (1st and 2nd arg)
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	int		tmp;
	char	*res;
	
	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] >= REG_NUMBER)
	{
		tmp = arg1 ^ arg2;
		proc->carry = (!tmp);
		if (!(res = itoua(tmp)))
			error(cor, "Failed to itoua in instr_xor");
		fill_register(cor, cor->arena[(proc->idx + proc->move + 1)
				% MEM_SIZE], res);
		free(res);
	}
}

/*
** S (RG | ID | D4), S (RG | ID | D4), D (RG)
*/

void		instr_xor(t_cor *cor, t_proc *proc)
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
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1]);		
	}
	else if (type == IND_CODE)
		arg1 = get_int_arg_val(cor, proc->idx + (get_int_arg_val(cor, proc->idx + proc->move + 1, IND_BYTES) % IDX_MOD), REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_int_arg_val(cor, (proc->idx + proc->move + 1) % MEM_SIZE, D4_BYTES);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec
			&& (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1)
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2]);
	}
	else if (type == IND_CODE)
		arg2 = get_int_arg_val(cor, proc->idx + (get_int_arg_val(cor, proc->idx + proc->move + 1, IND_BYTES) % IDX_MOD), REG_SIZE);
	else if (type == DIR_CODE)
		arg2 = get_int_arg_val(cor, (proc->idx + proc->move + 1) % MEM_SIZE, D4_BYTES);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
