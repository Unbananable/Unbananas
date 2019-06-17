/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/17 10:27:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** JUMP
** - opcode: 0x09
** - wait: 20
** - argcode: no
** - args: DIR(2)
** - addressing retriction: no
** - carry: no
** - description: If the carry is 1, move the proc by the number of bytes
**   indicated by the argument.
*/

void	instr_zjmp(t_cor *cor, t_proc *proc)
{
	t_bool	to_exec;

	to_exec = proc->carry;
	proc->move = get_short_arg_value(cor, proc->idx + 1) % IDX_MOD;
	if (cor->verbose & V_OPERATIONS)
	{
		ft_printf("P %4d | zjmp %d ", proc->n, proc->move);
		if (to_exec)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	if (!to_exec)
		proc->move = D2_BYTES + OPC_BYTE;
}
