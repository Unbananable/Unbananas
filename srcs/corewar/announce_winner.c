/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:57:49 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/24 12:13:10 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	announce_winner(t_cor *cor)
{
	int		winner_no;
	int		i;

	winner_no = cor->last_alive;
	i = -1;
	while (cor->champs[++i])
		if (cor->visual_on)
		{
			//
		}
		else
		{
		if (cor->champs[i]->player_no == winner_no)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", winner_no,
					cor->champs[i]->head.prog_name);
			return ;
		}
		}
	ft_printf("No winner...\n");
}
