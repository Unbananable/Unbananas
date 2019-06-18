/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:27:40 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/18 13:46:00 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES extracted from the 1st and 2nd args
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	int		tmp;
	int		addr;

	if (cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			&& cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			<= REG_NUMBER)
	{
		if (arg2 > 0 && arg1 > INT_MAX - arg2)
			tmp = INT_MAX;
		if (arg2 < 0 && arg1 < INT_MIN - arg2)
			tmp = INT_MIN;
		else
			tmp = arg1 + arg2;
		addr = get_int_arg_value(cor, proc->idx + tmp % IDX_MOD, D4_BYTES);
		proc->carry = (!addr);
		if (cor->verbose & V_OPERATIONS)
		{
			ft_printf("P %4d | ldi %d %d r%d\n", proc->n, arg1, arg2,
					cor->arena[restricted_addr(proc->idx + proc->move + 1)]);
			ft_printf("       | -> load from %d + %d = %d ", arg1, arg2, tmp);
			ft_printf("(with pc and mod %d)\n",
					restricted_addr(proc->idx + tmp % IDX_MOD));
		}
		regcpy(proc->regs[cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)] - 1], (void *)&addr);
	}
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
		proc->move += byte_offset(type);
	}
	else if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx
				+ get_int_arg_value(cor, proc->idx + proc->move + 1, IND_BYTES)
				% IDX_MOD), REG_SIZE);
	else
		arg1 = get_short_arg_value(cor, proc->idx + proc->move + 1);
	if (type != REG_CODE)
		proc->move += D2_BYTES;
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
		proc->move += byte_offset(type);
	}
	else if (type == DIR_CODE)
	{
		arg2 = get_short_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE);
		proc->move += D2_BYTES;
	}
	return (arg2);
}

/*
** INDIRECT LOAD
** - opcode: 0x0A
** - wait: 25
** - argcode: yes
** - args: REG/IND/DIR(2) REG/DIR(2) REG
** - addressing retriction: yes
** - carry: 1 if the sum of the arguments is 0, 1 otherwise
** - description: Stores the value of the address resulting from the sum of the
**   first two arguments in the register indicated by the third argument.
*/

void		instr_ldi(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE
				|| type == DIR_CODE));
	arg1 = first_arg(cor, proc, &to_exec, type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	arg2 = second_arg(cor, proc, &to_exec, type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
