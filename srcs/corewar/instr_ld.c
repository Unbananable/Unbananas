/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 19:03:02 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** First case: T_IND case
** Second case: T_DIR(4) case
*/

void	instr_ld(t_cor *cor, t_proc *proc)
{
	int		i;
	int		addr;

	i = -1;
	if (cor->arena[proc.idx + BYTE1] & 0b01000000)
	{
		cor->hex[0] = cor->arena[proc.idx + BYTES2];
		cor->hex[1] = cor->arena[proc.idx + BYTES3];
		addr = restricted_addr(cor, proc, ft_atoi_base(cor->hex, 16));
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + addr + i)];
		fill_register(cor, proc, BYTES4);
		proc.idx = cyd_val(proc.idx + BYTES5);
	}
	else
	{
		while (++i < 4)
			cor->hex[i] = cor->arena[cyd_val(proc.idx + BYTES2 + i)];
		fill_register(cor, proc, BYTES6);
		proc.idx = cyd_val(proc.idx + BYTES7);
	}
	proc.carry = (!ft_atoi_base(cor->hex, 16)) ? 1 : 0;
	ft_bzero(cor->hex, REG_SIZE);
}
