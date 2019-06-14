/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:01:40 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/14 13:50:33 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** FORK
** - opcode: 0x0C
** - wait: 800
** - argcode: no
** - args: DIR(2)
** - addressing retriction: yes
** - carry: no
** - description: Creates a new proc which is a clone of the current proc. It
**   is placed at the address indicated by the second parameter.
*/

void	instr_fork(t_cor *cor, t_proc *proc)
{
	int		arg1;
	t_proc	*new_proc;

	arg1 = get_short_arg_value(cor, (proc->idx + 1) % MEM_SIZE);
	new_proc = clone_proc(cor, proc);
	new_proc->wait = 0;
	new_proc->idx = (proc->idx + (arg1 % IDX_MOD)) % MEM_SIZE;
	cor->procs = add_proc(new_proc, cor->procs);
	proc->move = OPC_BYTE + D2_BYTES;
	if (cor->verbose & V_OPERATIONS)
		ft_printf("P %4d | fork %d (%d)\n", proc->n, arg1,
				restricted_addr(proc->idx + (arg1 % IDX_MOD)));
}
