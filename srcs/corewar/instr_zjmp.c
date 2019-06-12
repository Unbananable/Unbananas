/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/12 14:40:44 by anleclab         ###   ########.fr       */
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
	{
		proc->move = get_short_arg_value(cor, proc->idx + 1) % IDX_MOD;
		if (cor->verbose & V_OPERATIONS)
		{
			ft_putstr("P    ");
			ft_putnbr(proc->n + 1);
			ft_putstr(" | zjmp ");
			ft_putnbr(proc->move);
			ft_putstr(" OK\n");
		}
	}
	else
		proc->move = D2_BYTES + OPC_BYTE;
}
