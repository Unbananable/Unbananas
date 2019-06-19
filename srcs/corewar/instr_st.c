/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 13:19:48 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	int		src1;

	if (get_args(cor, proc))
	{
		src1 = get_arg_true_val(cor, proc, cor->args[0], true);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | st r%d ", proc->n, cor->args[0].val);
		if (cor->args[1].type == T_REG)
		{
			regcpy(proc->regs[cor->args[1].val - 1], (void *)&src1);
			if (cor->verbose & V_OPERATIONS)
				ft_printf("r%d\n", cor->args[1].val);
		}
		else if (cor->args[1].type == T_IND)
		{
			mapcpy(cor, proc, proc->idx + cor->args[1].val % IDX_MOD, (void *)&src1);
			if (cor->verbose & V_OPERATIONS)
				ft_printf("%d\n", cor->args[1].val);
		}
	}
}
