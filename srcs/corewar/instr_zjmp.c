/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 19:41:07 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** S (D2)
*/

void	instr_zjmp(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	short	arg;

	to_exec = (proc->carry);
	arg = ft_uchar_to_short_base(fill_hex(cor, (proc->idx + BYTE)
				% MEM_SIZE, D2_BYTES), 16);
	if (to_exec)
		proc->move = (restricted_addr(proc->idx, arg)) % MEM_SIZE;
	else
		proc->move = IND_BYTES + OPC_BYTE;
}
