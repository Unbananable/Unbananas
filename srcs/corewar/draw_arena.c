/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:54 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 15:37:31 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void draw_starting_arena(t_cor *cor)
{
	int i;
	int j;
	int idx;
	
	idx = 0;
	i = -1;
	while (++i < MEM_SIZE)
		cor->visu->attr_arena[i].owner = 0;
	i = -1;
	while (++i < cor->nb_champs)
	{
		j = -1;
		while (++j < (int)cor->champs[i]->head.prog_size)
			cor->visu->attr_arena[idx + j].owner = cor->champs[i]->player_no;
		idx += MEM_SIZE / cor->nb_champs;
	}
}

void draw_arena(t_cor *cor)
{
    int i;
    int j;
    int attribute;

    werase(cor->visu->arena);
    werase(cor->visu->arena_info);
    i = -1;
    while (++i < MEM_SIZE / 64)
    {
        j = -1;
        waddch(cor->visu->arena, ' ');
        while (++j < MEM_SIZE / 64)
        {
            attribute = get_attribute(cor, i * 64 + j);
            waddch(cor->visu->arena, ' ');
            wattron(cor->visu->arena, attribute);
            wprintw(cor->visu->arena, "%.2x", cor->arena[i * 64 + j]);
            wattroff(cor->visu->arena, attribute);
        }
        waddch(cor->visu->arena, ' ');
        waddch(cor->visu->arena, '\n');
    }
    box(cor->visu->arena_info, ACS_VLINE, ACS_HLINE);
    box(cor->visu->arena, ACS_VLINE, ACS_HLINE);
    wrefresh(cor->visu->arena_info);
    wrefresh(cor->visu->arena);
}