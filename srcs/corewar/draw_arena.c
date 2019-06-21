/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:54 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/21 16:25:50 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_starting_arena(t_cor *cor)
{
	int		i;
	int		j;
	int		idx;

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

/*
manager(t_cor *cor, int key)
{
	if (key == ' ')
		pause(cor);
		
}
*/

void	draw_arena(t_cor *cor, int key)
{
	int		i;
	int		j;
	int		attribute;
/*
	int key;

	key = wgetch(stdscr);
*/	if (key == ' ')
		cor->visu->is_running = !cor->visu->is_running;
	else 
		modify_speed_factor(cor, key);
	if (cor->curr_cycle != 1 && cor->visu->is_running == false)
	{
		wmove(cor->visu->arena_info, 2, 3);
		wprintw(cor->visu->arena_info, "** PAUSED ** ");
		wmove(cor->visu->arena_info, 6, 3);
		wprintw(cor->visu->arena_info, "Cycle : %d  ", cor->curr_cycle);
	}
	else
	{
		werase(cor->visu->arena);
		wprintw(cor->visu->arena, "\n\n");
		i = -1;
		while (++i < MEM_SIZE / 64)
		{
			j = -1;
			wprintw(cor->visu->arena, "  ");
			while (++j < MEM_SIZE / 64)
			{
				attribute = get_attribute(cor, i * 64 + j);
				waddch(cor->visu->arena, ' ');
				wattron(cor->visu->arena, attribute);
				wprintw(cor->visu->arena, "%.2x", cor->arena[i * 64 + j]);
				wattroff(cor->visu->arena, attribute);
				cor->visu->attr_arena[i * 64 + j].cursor = false;
			}
			wprintw(cor->visu->arena, " \n");
		}
		wattron(cor->visu->arena, COLOR_PAIR(GRAY_CURSOR));
		box(cor->visu->arena, '*', '*');
		wattroff(cor->visu->arena, COLOR_PAIR(GRAY_CURSOR));
		wrefresh(cor->visu->arena);

		manage_arena_info(cor);

		wattron(cor->visu->arena_info, COLOR_PAIR(GRAY_CURSOR));
		box(cor->visu->arena_info, '*', '*');
		wattroff(cor->visu->arena_info, COLOR_PAIR(GRAY_CURSOR));

		/* *BEST BONUS* */
		werase(cor->visu->arena_announce);
		wmove(cor->visu->arena_announce, 2, 5);
		wprintw(cor->visu->arena_announce, "SPEED: %d", cor->visu->speed);
		wattron(cor->visu->arena_announce, COLOR_PAIR(GRAY_CURSOR));
		box(cor->visu->arena_announce, '*', '*');
		wattroff(cor->visu->arena_announce, COLOR_PAIR(GRAY_CURSOR));
		wrefresh(cor->visu->arena_announce);
		/* ************ */
	}
	highlight_speed_button(cor);
	wrefresh(cor->visu->arena_info);
}
