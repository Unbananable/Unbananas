/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:15:42 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/17 17:37:22 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	draw_border(WINDOW *window)
{
	wattron(window, COLOR_PAIR(GRAY));
	box(window, '*', '*');
	wattroff(window, COLOR_PAIR(GRAY));
}

void		draw_arena(t_cor *cor)
{
	int		i;
	int		j;
	int		attr;

	werase(cor->visu->arena);
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			attr = get_attr(&cor->visu->attr_arena[i * 64 + j]);
			wattron(cor->visu->arena, attr);
			wprintw(cor->visu->arena, "%.2x", cor->arena[i * 64 + j]);
			wattroff(cor->visu->arena, attr);
			waddch(cor->visu->arena, ' ');
		}
		waddch(cor->visu->arena, '\n');
	}
	draw_border(cor->visu->arena);
	wrefresh(cor->visu->arena);
}