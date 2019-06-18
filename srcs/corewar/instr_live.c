/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/14 13:51:00 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** LIVE
** - opcode: 0x01
** - wait: 10
** - argcode: no
** - args: DIR(4)
** - addressing retriction: no
** - carry: no
** - description: Reports the proc as alive. Also reports the player whose
**   number is contained in the argument as alive, if it exists.
*/

void	instr_live(t_cor *cor, t_proc *proc)
{
	int		arg1;
	int		i;

	proc->last_live_cycle = cor->curr_cycle;
	cor->nb_live++;
	arg1 = get_int_arg_value(cor, proc->idx + 1, 4);
	if (cor->verbose & V_OPERATIONS)
		ft_printf("P %4d | live %d\n", proc->n, arg1);
	i = -1;
	while (++i < cor->nb_champs)
		if (arg1 * -1 == cor->champs[i]->player_no)
		{
			cor->last_alive = arg1 * -1;
			cor->champs[i]->last_live = cor->curr_cycle;
			cor->champs[i]->lives_in_curr_period++;
			if (cor->verbose & V_LIVES)
				ft_printf("Player %d (%s) is said to be alive\n", arg1 * -1,
						cor->champs[i]->head.prog_name);
			break;
		}
	proc->move = 5;
}
