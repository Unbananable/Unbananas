/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:33:15 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 represente to VALUES (taken from their respective register)
** we process the calculus with
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	sum;
	char	*res;

	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] < REG_NUMBER)
	{
		sum = arg1 - arg2;
		sum = (sum < INT_MIN) ? INT_MIN : sum;
		sum = (sum > INT_MAX) ? INT_MAX : sum;
		if (!(res = itoua((int)sum)))
			error(cor, "Failed to itoua in instr_sub");
		fill_register(cor, cor->arena[(proc->idx + proc->move + 1)
				% MEM_SIZE], res);
		free(res);
		proc->carry = (!sum);
	}
}

/*
** S (RG), S (RG), D (RG)
*/

void		instr_sub(t_cor *cor, t_proc *proc)
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
			arg1 = get_reg_value(proc->regs[arg1]);
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2]);
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
