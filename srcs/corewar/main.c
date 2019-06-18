/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/18 18:39:39 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	usage(void)
{
	ft_putstr_fd("usage: ./corewar [-v verbosity_level -dump nbr_cycles] ", 2);
	ft_putstr_fd("[[-n player_number] champion1.cor] ...\n", 2);
}

int		main(int ac, char **av)
{
	t_cor	cor;

	// [TO DO] visu

	ac--;
	av++;
	if (!ac)
		usage();
	initialize(&cor);
	if (get_options(&cor, &ac, &av) == ERROR)
	{
		usage();
		end(&cor);
	}
	get_champions(&cor, ac, av);
	order_champions(&cor);
	arena_setup(&cor);
//print_cor(&cor);
	
	introduce_champions(&cor);
	battle(&cor);
	announce_winner(&cor);
	

	
/* VISUUUUU */

	initscr();
	noecho();
	curs_set(0);
	cbreak();

	if (!(cor.visu = malloc(sizeof(t_visu))))
		error(&cor, "Malloc of the visu has failed");
	if (!(cor.visu->arena = newwin(HEIGHT, WIDTH, 1, 1)))
		error(&cor, "Visu arena newwin had failed");
	if (!(cor.visu->arena_info = newwin(HEIGHT, WIDTH / 3, 1, WIDTH + 1)))
		error(&cor, "Visu arena info newwin has failed");

	use_default_colors();
	start_color();

	init_color(COLOR_GRAY, 300, 300, 300);
	init_color(BLACK_B, 0, 0, 0);
	init_pair(GRAY, COLOR_GRAY, BLACK_B);
	init_pair(RED, COLOR_RED, BLACK_B);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
	init_pair(GREEN, COLOR_GREEN, BLACK_B);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
	init_pair(YELLOW, COLOR_YELLOW, BLACK_B);
	init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(YELLOW_LIVE, COLOR_WHITE, COLOR_YELLOW);
	init_pair(BLUE, COLOR_BLUE, BLACK_B);
	init_pair(BLUE_CURSOR, COLOR_BLACK, COLOR_BLUE);
	init_pair(BLUE_LIVE, COLOR_WHITE, COLOR_BLUE);
	init_pair(MAGENTA, COLOR_MAGENTA, BLACK_B);
	init_pair(MAGENTA_CURSOR, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(MAGENTA_LIVE, COLOR_WHITE, COLOR_MAGENTA);

	int i;
	int j;
	
	/* ASSIGN STARTING OWNERS */
	int idx;
	
	idx = 0;
	i = -1;
	while (++i < MEM_SIZE)
		cor.visu->attr_arena[i].owner = 0;
	i = -1;
	while (++i < cor.nb_champs)
	{
		j = -1;
		while (++j < (int)cor.champs[i]->head.prog_size)
			cor.visu->attr_arena[idx + j].owner = cor.champs[i]->player_no;
		idx += MEM_SIZE / cor.nb_champs;
	}
	/* ********************** */

	int attribute;

	int color;

	werase(cor.visu->arena);
	werase(cor.visu->arena_info);
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		waddch(cor.visu->arena, ' ');
		while (++j < MEM_SIZE / 64)
		{
			/* GET_ATTRIBUTE */
			if (cor.visu->attr_arena[i * 64 + j].owner == 1)
				color = COLOR_PAIR(RED);
			else if (cor.visu->attr_arena[i * 64 + j].owner == 2)
				color = COLOR_PAIR(GREEN);
			else if (cor.visu->attr_arena[i * 64 + j].owner == 3)
				color = COLOR_PAIR(YELLOW);
			else if (cor.visu->attr_arena[i * 64 + j].owner == 4)
				color = COLOR_PAIR(BLUE);
			else if (!(cor.visu->attr_arena[i * 64 + j].owner))
				color = COLOR_PAIR(GRAY);
			else
				color = COLOR_PAIR(MAGENTA);
			/* ************* */
			attribute = color;
			waddch(cor.visu->arena, ' ');
			wattron(cor.visu->arena, attribute);
			wprintw(cor.visu->arena, "%.2x", cor.arena[i * 64 + j]);
			wattroff(cor.visu->arena, attribute);
		}
		waddch(cor.visu->arena, ' ');
		waddch(cor.visu->arena, '\n');
	}







	box(cor.visu->arena_info, 0, 0);
	box(cor.visu->arena, 0, 0);
	wrefresh(cor.visu->arena_info);
	wrefresh(cor.visu->arena);

wgetch(cor.visu->arena);
wgetch(cor.visu->arena_info);
endwin();

/* ******** */
	
	end(&cor);
}
