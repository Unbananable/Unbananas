/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:37:00 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 17:14:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void init_visu(t_cor *cor)
{
    int i;

	initscr();
	noecho();
	curs_set(0);
	cbreak();
	if (!(cor->visu = malloc(sizeof(t_visu))))
		error(cor, "Malloc of the visu has failed");
	if (!(cor->visu->arena = newwin(HEIGHT, WIDTH, 1, 1)))
		error(cor, "Visu arena newwin had failed");
	if (!(cor->visu->arena_info = newwin(HEIGHT, WIDTH / 3, 1, WIDTH + 2)))
		error(cor, "Visu arena info newwin has failed");
/* *BEST BONUS* */
    if (!(cor->visu->arena_announce = newwin(5, WIDTH + WIDTH / 3 + 2, HEIGHT + 2, 1)))
        error(cor, "Visu arena announce newwin has failed");
/* ************ */
    i = -1;
    while (++i < MEM_SIZE)
    {
        cor->visu->attr_arena[i].live_bright = 0;
        cor->visu->attr_arena[i].store_bright = 0;
        cor->visu->attr_arena[i].cursor = false;
    }
}