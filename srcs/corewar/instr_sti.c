/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/12 17:28:20 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg2 is a restricted address and the target of the instruction
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	proc->carry = (!arg1);
	mapcpy(cor, (proc->idx + arg2) % MEM_SIZE, (void *)&arg1);
}

static int	first_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg1;

	arg1 = 0;
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[restricted_addr(proc->idx
						+ proc->move + 1)]) > REG_NUMBER || !arg1)
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
		if ((arg2 = cor->arena[restricted_addr((proc->idx + proc->move + 1)
						% MEM_SIZE)]) > REG_NUMBER || !arg2)
			*to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2 - 1]);
		proc->move += byte_offset(type);
	}
	if (type == IND_CODE)
		arg2 = get_int_arg_value(cor, (proc->idx
					+ get_int_arg_value(cor, (proc->idx + proc->move + 1)
					% MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg2 = (int)get_short_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE);
	if (type != REG_CODE)
		proc->move += D2_BYTES;
	return (arg2);
}

static int	third_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg3;

	arg3 = 0;
	if (type == REG_CODE)
	{
		if ((arg3 = cor->arena[restricted_addr((proc->idx
						+ proc->move + 1) % MEM_SIZE)]) > REG_NUMBER || !arg3)
			*to_exec = false;
		else
			arg3 = get_reg_value(proc->regs[arg3 - 1]);
		proc->move += byte_offset(type) + OPC_BYTE;
	}
	else if (type == DIR_CODE)
	{
		arg3 = (int)get_short_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE);
		proc->move += D2_BYTES + OPC_BYTE;
	}
	return (arg3);
}

/*
** S (RG) S (RG | ID | D2) D (RG | D2)
** if D2, value is short
*/

void		instr_sti(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;
	int		arg3;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	arg1 = first_arg(cor, proc, &to_exec, type);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE
				|| type == DIR_CODE));
	arg2 = second_arg(cor, proc, &to_exec, type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	arg3 = third_arg(cor, proc, &to_exec, type);
	if (to_exec)
		execute_instr(cor, proc, arg1, (arg2 + arg3) % IDX_MOD);
	if (cor->verbose & V_OPERATIONS)
	{
		ft_printf("P %4d | sti r%d %d %d\n", proc->n + 1, -arg1, arg2, arg3);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				arg2, arg3, arg2 + arg3, restricted_addr(proc->idx + (arg2
				+ arg3) % IDX_MOD));
	}
}
