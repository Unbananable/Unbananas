/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lfork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:39:50 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/06 16:07:28 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    instr_fork(t_cor *cor, t_proc *proc)
{
    int     arg1;
    t_proc  *new_proc;

    arg1 = get_short_arg_value(cor, proc->idx + 1, D2_BYTES);
    new_proc = clone_proc(cor, proc);
    new_proc->wait = 0;
    new_proc->idx = (proc->idx + arg1) % MEM_SIZE;
    cor->procs = add_proc(new_proc, cor->procs);
    proc->move = OPC_BYTE + byte_offset(D2_BYTES);
}