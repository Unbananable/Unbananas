/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/14 13:51:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg is the int VALUE registered into the 1st argument (register)
** type is the kind of the destination (register or indirect)
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg, int type)
{
	if (type == REG_CODE && cor->arena[restricted_addr(proc->idx
				+ proc->move + 1)] && cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)] <= REG_NUMBER)
	{
		regcpy(proc->regs[cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)] - 1], (void *)&arg);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("r%d\n", cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)]);
	}
	else if (type == IND_CODE)
	{
		if (cor->verbose & V_OPERATIONS)
			ft_printf("%d\n", get_short_arg_value(cor, proc->idx
					+ proc->move + 1));
		mapcpy(cor, proc->idx + (get_short_arg_value(cor, (proc->idx
							+ proc->move + 1)) % IDX_MOD), (void *)&arg);
	}
}

/*
** DIRECT STORE
** - opcode: 0x03
** - wait: 5
** - argcode: yes
** - args: REG REG/IND
** - addressing retriction: yes
** - carry: 1 if the first argument is 0, 0 otherwise
** - description: Loads the content of the register indicated by the first
**   argument into the second argument (a register or in the VM)
*/

void		instr_st(t_cor *cor, t_proc *proc)
{
	int			type;
	t_bool		to_exec;
	int			arg;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (type == REG_CODE)
	{
		if ((arg = cor->arena[restricted_addr((proc->idx
							+ proc->move + 1))]) > REG_NUMBER || !arg)
			to_exec = false;
		else
		{
			if (cor->verbose & V_OPERATIONS)
				ft_printf("P %4d | st r%d ", proc->n, arg);
			arg = get_reg_value(proc->regs[arg - 1]);
		}
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE));
	if (to_exec)
		execute_instr(cor, proc, arg, type);
	proc->move += byte_offset(type) + OPC_BYTE;
}
