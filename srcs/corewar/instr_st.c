/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 17:17:24 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** First case: T_REG case
** Second case: T_IND case
*/

void		instr_st(t_cor *cor, unsigned int proc_id)
{
	int		i;
	int		addr;

	i = -1;
	if (cor->arena[cor->procs[proc_id].idx + BYTE1] & 0b00100000)
	{
		while (++i < REG_SIZE)
			cor->reg[cor->arena[cyd_val(cor->procs[proc_id].idx + BYTES3)]
				- 1][i] = cor->reg[cor->arena[cyd_val(cor->procs[proc_id].idx
				+ BYTES2)] - 1][i];
		cor->procs[proc_id].idx = set_next_idx(cor, proc_id, BYTES4);
	}
	else
	{
		cor->hex[0] = cor->arena[cor->procs[proc_id].idx + BYTES3];
		cor->hex[1] = cor->arena[cor->procs[proc_id].idx + BYTES4];
		addr = restricted_addr(cor, proc_id, ft_atos_base(cor->hex, 16));
		ft_bzero(cor->hex, REG_SIZE);
		while (++i < REG_SIZE)
			cor->arena[cyd_val(addr
					+ i)] = cor->reg[cor->arena[cyd_val(cor->procs[proc_id].idx
				+ BYTES2)]][i];
		cor->procs[proc_id].idx = set_next_idx(cor, proc_id, BYTES5);
	}
	cor->procs[proc_id].cooldown = CYCLE_ST;
}
