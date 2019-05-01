/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 19:06:41 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		instr_live(t_cor *cor, t_proc *proc)
{
	int	i;
	int	target;

	i = -1;
	proc.last_live_cycle = cor->curr_cycle;
	while (++i < DIR_SIZE)
		cor->hex[i] = cor->arena[cyd_val(proc.idx + i)];
	target = -(ft_atoi_base(cor->hex, 16));
	ft_bzero(cor->hex, REG_SIZE);
	if (target <= cor->nb_champ)
	{
		cor->champ[target - 1]->curr_lives++;
		cor->champ[target - 1]->last_live = cor->curr_cycle;
		cor->last_alive = target;
		if (cor->option->verbose % 2)
		{
			ft_putstr_fd("Player ", STDOUT);
			ft_putnbr_fd(target, STDOUT);
			ft_putstr_fd(" (", 1);
			ft_putstr_fd(cor->champ[target - 1]->head.prog_name, STDOUT);
			ft_putstr_fd(") is said to be alive\n", STDOUT);
		}
	}
	proc.idx = cyd_val(proc.idx + BYTES5);
}
