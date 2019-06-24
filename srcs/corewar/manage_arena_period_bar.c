/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arena_period_bar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:15:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/24 13:18:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void manage_arena_period_bar(t_cor *cor)
{
    static int k = 0;

    wattron(cor->visu->arena_period_bar, COLOR_PAIR(SPEED_HIGHLIGHT));
    while (k < ((double)cor->curr_cycle_period / cor->cycle_to_die) * (WIDTH
     + WIDTH / 3) && k < (WIDTH + WIDTH / 3) - 2)
    {
        k++;
        wmove(cor->visu->arena_period_bar, 2, k + 1);
        waddch(cor->visu->arena_period_bar, ' ');
    }
    wattroff(cor->visu->arena_period_bar, COLOR_PAIR(SPEED_HIGHLIGHT));
    if ((int)cor->curr_cycle_period == 0)
    {
        wmove(cor->visu->arena_period_bar, 2, 3);
        k = -1;
        while (++k < (WIDTH + WIDTH / 3) - 2)
            waddch(cor->visu->arena_period_bar, ' ');
        k = 0;
    }
    wattron(cor->visu->arena_period_bar, COLOR_PAIR(GRAY_CURSOR));
    box(cor->visu->arena_period_bar, '*', '*');
    wattroff(cor->visu->arena_period_bar, COLOR_PAIR(GRAY_CURSOR));
    wrefresh(cor->visu->arena_period_bar);
}