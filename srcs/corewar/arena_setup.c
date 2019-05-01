/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:28:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/01 20:48:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	place_champions(t_cor *cor)
{
	int				i;
	unsigned int	j;

	i = -1;
	while (++i < cor->nb_champs)
	{
		j = 0;
		while (j < cor->champs[i]->head.prog_size)
		{
			cor->arena[i * MEM_SIZE / cor->nb_champs + j]
				= cor->champs[i]->redcode[j];
			j++;
		}
	}
}

void		initialize_procs(t_cor *cor)
{
	int		i;
	t_proc	*new;
	int		*player_no;

	i = -1;
	while (++i < cor->nb_champs)
	{
		if (!(new = new_proc()))
			error(cor, "malloc failed");
		new->n = i;
		new->carry = false;
		new->last_live_cycle = 0;
		new->idx = i * MEM_SIZE / cor->nb_champs;
		if (!(player_no = (int *)malloc(sizeof(int))))
			error(cor, "malloc failed");
		*player_no = -1 * cor->champs[i]->player_no;
		memcpy_big(new->regs[0], player_no, sizeof(char) * REG_SIZE);
		free(player_no);
		cor->procs = add_proc(new, cor->procs);
	}
}

void	arena_setup(t_cor *cor)
{
	place_champions(cor);
	//TO DO: Placer et initialiser les carriages [WIP]
	initialize_procs(cor);
}
