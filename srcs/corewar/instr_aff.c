/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:08:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/13 09:57:54 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** AFF
** - opcode: 0x0F
** - wait: 2
** - argcode: yes
** - args: REG
** - addressing retriction: no
** - carry: 1 if the content of the argument is 0, 1 otherwise
** - description: Displays the character corresponding to the argument (mod 256)
*/

void		instr_aff(t_cor *cor, t_proc *proc)
{
	t_bool	to_exec;
	int		type;
	char	arg1;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
	{
		arg1 = cor->arena[restricted_addr(proc->idx + proc->move + 1)];
		proc->carry = (!arg1);
		write(1, &arg1, 1);
	}
	proc->move += byte_offset(type);
	proc->move += OPC_BYTE;
}
