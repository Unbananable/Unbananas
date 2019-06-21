/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:22:44 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/21 16:34:12 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    apply_speed(t_cor *cor)
{
	int i;
	int key;
	
	i = 0;
	if (cor->visu->speed == -2)
	{
		while (++i < VERY_SLOW)
		{
			key = wgetch(stdscr);
			if (key != -1)
				draw_arena(cor, key);
		}
	}
	else if (cor->visu->speed == -1)
	{
		while (++i < SLOW)
		{
			key = wgetch(stdscr);
			if (key != -1)
				draw_arena(cor, key);
		}
	}
	else if (cor->visu->speed == 0)
	{
		while (++i < NORMAL)
		{
			key = wgetch(stdscr);
			if (key != -1)
				draw_arena(cor, key);
		}
	}
	else if (cor->visu->speed == 1)
	{
		while (++i < FAST)
		{
			key = wgetch(stdscr);
			if (key != -1)
				draw_arena(cor, key);
		}
	}
}

void	modify_speed_factor(t_cor *cor, int key)
{
	if (key == 'q')
		cor->visu->speed = -2;
	else if (key == 'w' && cor->visu->speed != -2)
		cor->visu->speed = -1;
	else if (key == 'e')
		cor->visu->speed = 0;
	else if (key == 'r')
		cor->visu->speed = 1;
	else if (key == 't')
		cor->visu->speed = 2;
}

void	highlight_speed_button(t_cor *cor)
{
	wmove(cor->visu->arena_info, 4, 3);
	wprintw(cor->visu->arena_info, "Speed : << | < | o | > | >>");
	wattron(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
    if (cor->visu->speed == -2)
	{
		wmove(cor->visu->arena_info, 4, 11);
		wprintw(cor->visu->arena_info, "<<");
	}
	else if (cor->visu->speed == -1)
	{
		wmove(cor->visu->arena_info, 4, 16);
		wprintw(cor->visu->arena_info, "<");
	}
	else if (cor->visu->speed == 0)
	{
		wmove(cor->visu->arena_info, 4, 20);
		wprintw(cor->visu->arena_info, "o");
	}
	else if (cor->visu->speed == 1)
	{
		wmove(cor->visu->arena_info, 4, 24);
		wprintw(cor->visu->arena_info, ">");
	}
	else if (cor->visu->speed == 2)
	{
		wmove(cor->visu->arena_info, 4, 28);
		wprintw(cor->visu->arena_info, ">>");
	}
	wattroff(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
}
