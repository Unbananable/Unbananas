/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:57:49 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/12 17:03:48 by anleclab         ###   ########.fr       */
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
		if (cor->champs[i]->player_no == winner_no)
			ft_printf("Contestant %d, \"%s\" has won !", winner_no,
					cor->champs[i]->head.prog_name);
}
