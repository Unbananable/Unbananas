/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 15:05:24 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	instr_ld(t_cor *cor, unsigned int proc_id)
{
	int		i;
	int		addr;

	i = -1;
	if (cor->arena[cor->procs[proc_id].idx + 1] & 0b01000000)
	{
		cor->hex[0] = cor->arena[procs[proc_id].idx + 2BYTES];
		cor->hex[1] = cor->arena[procs[proc_id].idx + 3BYTES];
		addr = cycled_addr(cor, proc_id, ft_atoi_base(cor->hex, 16));
		while (++i < REG_SIZE)
			cor->hex[i] = cor->arena[cor->procs[proc_id].idx + addr + i];
		fill_register(cor, cor->arena[cor->procs[proc_id].idx + 4BYTES], cor->hex);
		cor->procs[proc_id].idx = set_next_idx(cor, proc_id, 5BYTES);
	}
	else
	{
		while (++i < 4)
			cor->hex[i] = cor->arena[cor->procs[proc_id].idx + 2BYTES + i];
		fill_register(cor, cor->arena[cor->procs[proc_id].idx + 6BYTES], cor->hex);
		cor->procs[proc_id].idx = set_next_idx(cor, proc_id, 7BYTES);
	}
	cor->procs[proc_id].carry = (!ft_atoi_base(hex, 16)) ? 1 : 0;
	ft_bzero(cor->hex, REG_SIZE + 1);
	cor->procs[proc_id].cooldown = CYCLE_LD;
}
