/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:33:15 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	sum;
	char	*res;

	if (cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] >= REG_NUMBER)
	{
		sum = ft_uchar_to_int_base(proc->regs[arg1], 16)
			+ ft_uchar_to_int_base(proc->regs[arg2], 16);
		sum = (sum < INT_MIN) ? INT_MIN : sum;
		sum = (sum > INT_MAX) ? INT_MAX : sum;
		if (!(res = ft_int_to_uchar((int)sum)))
			error(cor, "Failed to ft_int_to_uchar in instr_add");
		fill_register(cor, cor->arena[(proc->idx + proc->move + 1)
				% MEM_SIZE], res);
		free(res);
		proc->carry = (!sum);
	}
}

/*
** S (RG), S (RG), D (RG)
*/

void		instr_add(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if ((arg1 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
		to_exec = false;
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if ((arg2 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
		to_exec = false;
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
