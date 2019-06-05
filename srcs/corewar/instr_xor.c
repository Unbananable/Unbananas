/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_xor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:33:30 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	int		tmp;
	char	*res;
	
	if (is_register(cor->arena[(proc->idx + proc->move) % MEM_SIZE]))
	{
		tmp = arg1 ^ arg2;
		proc->carry = (!tmp);
		if (!(res = ft_int_to_uchar(tmp)))
			error(cor, "Failed to ft_int_to_uchar in instr_xor");
		fill_register(cor, cor->arena[(proc->idx + proc->move)
				% MEM_SIZE], res);
		free(res);
	}
}

/*
** S (RG | ID | D4), S (RG | ID | D4), D (RG)
*/

void			instr_xor(t_cor *cor, t_proc *proc)
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
	proc->move += byte_offset(type);
	if (type == REG_CODE)
		if ((arg1 = cor->arena[(proc->idx + proc->move)
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
	else if (type == IND_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move, IND_BYTES), 16), REG_SIZE), 16);
	else if (type == DIR_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move, D4_BYTES), 16);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec
			&& (type == REG_CODE || type == IND_CODE || type == DIR_CODE));
	proc->move += byte_offset(type);
	if (type == REG_CODE)
		if ((arg2 = cor->arena[(proc->idx + proc->move)
					% MEM_SIZE]) >= REG_NUMBER)
			to_exec = false;
	else if (type == IND_CODE)
		arg1 = ft_uchar_to_int_base(fill_hex(cor, ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move, IND_BYTES), 16), REG_SIZE), 16);
	else if (type == DIR_CODE)
		arg2 = ft_uchar_to_int_base(fill_hex(cor, proc->idx + proc->move, D4_BYTES), 16);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += OPC_BYTE;
}
