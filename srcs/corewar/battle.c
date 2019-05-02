/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 15:02:38 by anleclab         ###   ########.fr       */
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
			if (!cache->wait) //Si le temps d'attente est expire, executer
			{
				//TO DO: Executer l'instruction
				//TO DO: Update le processus (position)
			}
			else //Si le temps d'attende n'est pas expire, le diminuer d'un cycle
				cache->wait--;
			cache = cache->next; //Passer au processus suivant
		}
		if (cor->curr_cycle % cor->cycle_to_die == 0)
		{
			//TO DO: Kill les processus qui n'ont pas fait de live
			if (cor->nb_live >= NBR_LIVE) //Si au moins NBR_LIVE instructions
					//live ont ete performee dans la periode, decrementer le
					//nombre de cycle par periode
				cor->cycle_to_die = (cor->cycle_to_die > CYCLE_DELTA)
						? cor->cycle_to_die - CYCLE_DELTA : 1;
		}
		cor->curr_cycle++; //Incrementer le cycle en cours
	}
}
