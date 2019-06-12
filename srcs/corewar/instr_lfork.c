/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lfork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:39:50 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/12 17:22:46 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	instr_lfork(t_cor *cor, t_proc *proc)
{
	int		arg1;
	t_proc	*new_proc;

	arg1 = get_short_arg_value(cor, (proc->idx + 1) % MEM_SIZE);
	new_proc = clone_proc(cor, proc);
	new_proc->wait = 0;
	new_proc->idx = restricted_addr(proc->idx + arg1);
	cor->procs = add_proc(new_proc, cor->procs);
	proc->move = OPC_BYTE + D2_BYTES;
	if (cor->verbose & V_OPERATIONS)
		ft_printf("P %4d | lfork %d (%d)\n", proc->n + 1, arg1,
				restricted_addr(proc->idx + arg1));
}
