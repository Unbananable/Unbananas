/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 17:17:40 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	sum;
	char	*res;

	sum = ft_uchar_to_int_base(proc->regs[arg1], 16)
		+ ft_uchar_to_int_base(proc->regs[arg2], 16);
	sum = (sum < INT_MIN) ? INT_MIN : sum;
	sum = (sum > INT_MAX) ? INT_MAX : sum;
	if (!(res = ft_int_to_uchar((int)sum)))
		error(cor, "Failed to ft_itoa in instr_add");
	fill_register(cor, cor->arena[(proc->idx + proc->move) % MEM_SIZE], res);
	free(res);
	proc->carry = (!sum) ? 1 : 0;
}

/*
** Takes 3 T_REG as parameters
*/

int			instr_add(t_cor *cor, t_proc *proc)
{
	int		type;
	int		to_exec;
	int		arg1;
	int		arg2;

	to_exec = 1;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	proc->move += byte_offset(type);
	arg1 = cor->arena[cyd_val(proc->idx + proc->move)];
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	proc->move += byte_offset(type);
	arg2 = cor->arena[cyd_val(proc->idx + proc->move)];
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE) 1 : 0;
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += OPC_BYTE;
}
