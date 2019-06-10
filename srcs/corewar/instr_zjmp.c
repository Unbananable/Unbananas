/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/10 12:27:16 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** S (D2)
*/

void	instr_zjmp(t_cor *cor, t_proc *proc)
{
	t_bool	to_exec;

	to_exec = (proc->carry);
	if (to_exec)
		proc->move = (proc->idx + (get_short_arg_value(cor, (proc->idx + 1) % MEM_SIZE) % IDX_MOD)) % MEM_SIZE;
	else
		proc->move = D2_BYTES + OPC_BYTE;
}
