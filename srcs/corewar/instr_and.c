/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:33:09 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	int		tmp;
	char	*res;
	
	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] >= REG_NUMBER)
	{
		tmp = arg1 & arg2;
		proc->carry = (!tmp);
		if (!(res = ft_int_to_uchar(tmp)))
			error(cor, "Failed to ft_int_to_uchar in instr_and");
		fill_register(cor, cor->arena[(proc->idx + proc->move + 1)
				% MEM_SIZE], res);
		free(res);
	}
}

/*
** S (RG | ID | D4), S (RG | ID | D4), D (RG)
*/

void		instr_and(t_cor *cor, t_proc *proc)
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
			arg1 = ft_uchar_to_int_base(proc->regs[arg1], 16);		
	}
	else if (type == IND_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + (ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move + 1, IND_BYTES), 16) % IDX_MOD), REG_SIZE), 16);
	else if (type == DIR_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, (proc->idx + proc->move + 1)
					% MEM_SIZE, D4_BYTES), 16);
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
			arg2 = ft_uchar_to_int_base(proc->regs[arg2], 16);
	}
	else if (type == IND_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + (ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move + 1, IND_BYTES), 16) % IDX_MOD), REG_SIZE), 16);
	else if (type == DIR_CODE)
		arg2 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move + 1, D4_BYTES), 16);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
