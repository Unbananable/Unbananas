/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 09:08:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** INDIRECT STORE
** - opcode: 0x0B
** - wait: 25
** - argcode: yes
** - args: REG REG/IND/DIR(2) IND/DIR(2)
** - addressing retriction: yes
** - carry: no
** - description: Stores the content of the register indicated by the first
**   argument at the address indicated by the sum of the second and third
**   arguments.
*/

void		instr_sti(t_cor *cor, t_proc *proc)
{
	int		dest1;
	int		dest2;

	if (get_args(cor, proc))
	{
		dest1 = get_arg_true_val(cor, proc, cor->args[1], true);
		dest2 = get_arg_true_val(cor, proc, cor->args[2], true);
		mapcpy(cor, proc->idx + ((dest1 + dest2) % IDX_MOD), proc->regs[cor->args[0].val - 1]);
		if (cor->verbose & V_OPERATIONS)
		{
			ft_printf("P %4d | sti r%d %d %d\n", proc->n, cor->args[0].val, dest1, dest2);
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
					dest1, dest2, (dest1 + dest2), proc->idx + (dest1
					+ dest2) % IDX_MOD);
		}
	}
}
