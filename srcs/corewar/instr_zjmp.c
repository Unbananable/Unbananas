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

	to_exec = (proc->carry);
	if (to_exec)
		proc->move = proc->idx + (ft_uchar_to_short_base(fill_hex(cor, proc->idx + 1, D2_BYTES), 16) % IDX_MOD);
	else
		proc->move = D2_BYTES + OPC_BYTE;
}
