/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 11:44:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg is the int VALUE registered into the 1st argument (register)
** type is the kind of the destination (register or indirect)
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg, int type)
{
	char	*res;
	short	tmp;
	short	i;

	if (!(res = itoua(arg)))
		error(cor, "Failed to itoua in instr_st");
	if (type == REG_CODE && cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE] < REG_NUMBER)
		fill_register(cor, cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE], res);
	else if (type == IND_CODE)
	{
		i = -1;
		tmp = proc->idx + (get_short_arg_val(cor, proc->idx + proc->move + 1, IND_BYTES) % IDX_MOD);
		while (++i < REG_SIZE)
			cor->arena[(tmp + i) % MEM_SIZE] = res[i];
	}
	free(res);
}

/*
** S (RG) D (RG | ID)
** if ID as 2nd arg, value is short
*/

void		instr_st(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (type == REG_CODE)
	{
		if ((arg = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
		else
			arg = get_reg_value(proc->regs[arg]);
	}
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE));
	if (to_exec)
		execute_instr(cor, proc, arg, type);
	proc->move += byte_offset(type) + OPC_BYTE;
}
