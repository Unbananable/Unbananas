/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:20:01 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/30 14:36:50 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Takes as second parameter the index of the current OPC (01 for "live").
** Returns 0 if the player exists, execute live and returns 1 else.
*/

int		action_live(t_cor *cor, int idx)
{
	if (cor->arena + (idx + 1) != UCHAR_MAX || cor->arena + (idx + 2) != UCHAR_MAX || cor->arena + (idx + 3) != UCHAR_MAX)
		return (0);
	if (cor->arena + (idx + 4) < cor->max_player) //TODO set max_player apres le parsing du nombre de champ (exemple: si 4 champs, max player = 0xFC, si 3 0xFD, 2 0xFE, 1 0xFF)
		return (0);
	else
	{
		cor->champ->curr_lives[-(cor->arena + (idx + 4)) - 1]++;
		cor->champ->last_lives[-(cor->arena + (idx + 4)) - 1] = cor->curr_cycle;
		return (1);
	}
}
