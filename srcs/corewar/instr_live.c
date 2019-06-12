/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/12 09:56:33 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** S (D4)
*/

void	instr_live(t_cor *cor, t_proc *proc)
{
	int		arg1;

	proc->last_live_cycle = cor->curr_cycle;
	arg1 = get_int_arg_value(cor, (proc->idx + 1) % MEM_SIZE, D4_BYTES);
	cor->nb_live++;
	if (arg1 * -1 > 0 && arg1 * -1 <= cor->nb_champs)
		cor->last_alive = arg1 * -1;
	proc->move = OPC_BYTE + byte_offset(DIR_CODE);
}
