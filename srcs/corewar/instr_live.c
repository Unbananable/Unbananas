/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 17:15:29 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		instr_live(t_cor *cor, unsigned int proc_id)
{
	int	i;
	int	target;

	i = -1;
	while (++i < DIR_SIZE)
		cor->hex[i] = cor->arena[cyd_val(cor->procs[proc_id].idx + i)];
	target = -(ft_atoi_base(cor->hex, 16));
	ft_bzero(cor->hex, REG_SIZE);
	if (target <= cor->nb_champ)
	{
		cor->champ[-(cor->arena[cor->procs[proc_id].idx
					+ REG_SIZE]) - 1]->curr_lives++;
		cor->champ[-(cor->arena[cor->procs[proc_id].idx
					+ REG_SIZE]) - 1]->last_lives = cor->curr_cycle;
		cor->last_alive = -(cor->arena[cor->procs[proc_id].idx + 4]);
		cor->procs[proc_id].cooldown = CYCLE_LIVE;
		if (cor->option->verbose % 2)
		{
			ft_putstr_fd("Player ", STDOUT);
			ft_putnbr_fd(target, STDOUT);
			ft_putstr_fd(" (", 1);
			ft_putstr_fd(cor->champ[-(cor->arena[cor->procs[proc_id].idx
							+ REG_SIZE]) - 1]->name, STDOUT);
			ft_putstr_fd(") is said to be alive\n", STDOUT);
		}
	}
	cor->procs[proc_id].idx = set_next_idx(cor, proc_id, BYTES5);
}
