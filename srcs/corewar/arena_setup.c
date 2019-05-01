/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:28:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 19:00:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_champions(t_cor *cor)
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

void	arena_setup(t_cor *cor)
{
	//TO DO: Placer les champions dans l'arene [WIP anleclab]
	place_champions(cor);
	//TO DO: Placer et initialiser les carriages
}
