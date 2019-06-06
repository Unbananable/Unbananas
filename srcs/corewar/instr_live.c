/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 10:22:30 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//WIP
//C est les proc qui vivent et pas les champs, une partie sarrete lorsque tous les process sont morts

#include "corewar.h"

/*
** S (D4)
*/

void instr_live(t_cor *cor, t_proc *proc)
{
	int i;
	int target;
	t_bool to_exec;

	i = -1;
	to_exec = true;
	proc->last_live_cycle = cor->curr_cycle;
	while (++i < 3)
		if (!cor->arena[(proc->idx + i + 1) % MEM_SIZE])
			to_exec = false;
	target = -(cor->arena[(proc->idx + i + 1) % MEM_SIZE]);
	if (to_exec && target <= cor->nb_champs)
	{
		//Make the champ live
		//Definir le dernier champ qui a dit LIVE (via le numero du cycle du dernier live par exemple) ou en definissant un COR->LAST_ALIVE au choix;
		if (cor->verbose % 2)
		{
			//MSG I M ALIVE
		}
		//Actualiser move
	}
	else
		//Actualiser move dans le cas echeant
}

/*
	while (++i < DIR_SIZE)
		cor->hex[i] = cor->arena[cyd_val(proc->idx + i)];
	target = -(ft_uchar_to_int_base(cor->hex, 16));
	ft_bzero(cor->hex, REG_SIZE);
	if (target <= cor->nb_champ)
	{
		cor->nb_live++;
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
		proc->move = REG_SIZE + BYTE1;
		return (1);
	}
	return (0);
}
*/