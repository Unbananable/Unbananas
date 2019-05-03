/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/03 12:27:35 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void   battle(t_cor *cor)
{
	t_proc	*cache;

	while (cor->procs) //Tant que tous les processus ne sont pas morts
	{
		cache = cor->procs;
		while (cache) //Parcourir tous les processus l'un a la suite de l'autre
		{
			if (!cache->wait) //Si le proc a bouge au cycle precedent
				//TO DO: Recuperer le opcode et le wait
			if (!(--cache->wait)) //Si le temps d'attente est expire, executer
			{
				//TO DO: Executer l'instruction
				//TO DO: Update le processus (position)
			}
			cache = cache->next; //Passer au processus suivant
		}
		if (cor->cycle_to_die <= 0
				|| cor->curr_cycle_period == (unsigned int)cor->cycle_to_die)
		{
			//TO DO: Kill les processus qui n'ont pas fait de live
			if (cor->nb_live >= NBR_LIVE || cor->nb_checks == MAX_CHECKS)
					//Si au moins NBR_LIVE instructions live ont ete performee
					//dans la periode, ou si le nombre de cycle par periode n'a
					//pas ete decremente depuis MAX_CHECKS, decrementer le
					//nombre de cycle par periode
			{
				cor->cycle_to_die -= CYCLE_DELTA;
				cor->nb_checks = 0;
			}
			else
				cor->nb_checks++;
			cor->curr_cycle_period = 0;
		}
		cor->curr_cycle++; //Incrementer le cycle en cours
		cor->curr_cycle_period++;
	}
}
