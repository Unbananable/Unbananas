/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:54 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 18:13:22 by dtrigalo         ###   ########.fr       */
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
        }
        wprintw(cor->visu->arena, " \n");
    }
    wattron(cor->visu->arena, COLOR_PAIR(GRAY_CURSOR));
    box(cor->visu->arena, '*', '*');
    wattroff(cor->visu->arena, COLOR_PAIR(GRAY_CURSOR));
    wrefresh(cor->visu->arena);
    
/* MANAGE ARENA INFO */
    int y;

    y = 2;
    werase(cor->visu->arena_info);
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] ** PAUSED / RUNNING **");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] Cycles per second limitation : NUMBER");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] Cycle : NUMBER");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] Processes : NUMBER");
    /* WHILE CHAMPIONS */
    y += 3;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] Player NUMBER : NAME(colored)");
    y += 1;
    wmove(cor->visu->arena_info, y, 5);
    wprintw(cor->visu->arena_info, "[WIP] Last live :                NUMBER");
    y += 1;
    wmove(cor->visu->arena_info, y, 5);
    wprintw(cor->visu->arena_info, "[WIP] Lives in current period :  NUMBER");
    /* END WHILE */
    y += 3;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] CYCLE_TO_DIE : NUMBER");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] CYCLE_DELTA : NUMBER");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] NBR_LIVE : NUMBER");
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "[WIP] MAX_CHECKS : NUMBER");

    wattron(cor->visu->arena_info, COLOR_PAIR(GRAY_CURSOR));
    box(cor->visu->arena_info, '*', '*');
    wattroff(cor->visu->arena_info, COLOR_PAIR(GRAY_CURSOR));
    wrefresh(cor->visu->arena_info);
/* ***************** */

/* *BEST BONUS* */
werase(cor->visu->arena_announce);
wmove(cor->visu->arena_announce, 2, 5);
wprintw(cor->visu->arena_announce, " [WIP] ANLECLAB IS PURRRRFECT !! Miaou ~");
wattron(cor->visu->arena_announce, COLOR_PAIR(GRAY_CURSOR));
box(cor->visu->arena_announce, '*', '*');
wattroff(cor->visu->arena_announce, COLOR_PAIR(GRAY_CURSOR));
wrefresh(cor->visu->arena_announce);
/* ************ */

}

/* WORK FOR TOMORROW

_Big fonction arena_info (dispatcher)
_Fonctions pour l evolution des 4 constantes (cycle to die...)
_Fonction cycle number
_Fonction process number
_Fonction while affichage du numero + nom champions
    _Fonctions last live + lives in current period (actualisation des cor->visu->var dans instr_live)

_Mise en place des actions / vitesse cycles

*/

