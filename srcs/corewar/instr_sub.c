/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/13 09:51:16 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 represente to VALUES (taken from their respective register)
** we process the calculus with
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long long	sum;

	if (cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			&& cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			<= REG_NUMBER)
	{
		sum = arg1 - arg2;
		proc->carry = (!sum);
		sum = (sum < INT_MIN) ? INT_MIN : sum;
		sum = (sum > INT_MAX) ? INT_MAX : sum;
		regcpy(proc->regs[cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)] - 1], (void *)&sum);
	}
}

static int	first_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg1;

	arg1 = 0;
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[restricted_addr(proc->idx + proc->move + 1)])
				> REG_NUMBER || !arg1)
			*to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1 - 1]);
	}
	return (arg1);
}

static int	second_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg2;

	arg2 = 0;
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[restricted_addr(proc->idx + proc->move + 1)])
				> REG_NUMBER || !arg2)
			*to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2 - 1]);
	}
	return (arg2);
}

/*
** SUBSTRACTION
** - opcode: 0x05
** - wait: 10
** - argcode: yes
** - args: REG REG REG
** - addressing retriction: no
** - carry: 1 if the substraction is 0, 0 otherwise
** - description: Substracts the content of the second register from the first
**   register and stores the result in the third register
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
	arg1 = first_arg(cor, proc, &to_exec, type);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	arg2 = second_arg(cor, proc, &to_exec, type);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
