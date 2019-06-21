/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:59:59 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 14:05:07 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.c"

/*
** Initializes the t_cor structure.
*/

void	initialize(t_cor *cor)
{
	cor->champs = NULL;
	if (!(cor->arena = (unsigned char *)malloc(sizeof(unsigned char)
			* MEM_SIZE)))
		error(cor, "malloc failed");
	ft_bzero(cor->arena, sizeof(unsigned char) * MEM_SIZE);
	cor->procs = NULL;
	cor->curr_cycle = 0;
	cor->curr_cycle_period = 0;
	cor->cycle_to_die = CYCLE_TO_DIE;
	cor->nb_live = 0;
	cor->nb_checks = 0;
	cor->last_alive = 0;
	cor->dump = false;
	cor->verbose = 0;
	cor->nb_procs = 0;
	cor->new_proc_n = 1;
	cor->op_tab = op_tab;
	cor->visual_on = false;
}
