/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 13:32:05 by dtrigalo         ###   ########.fr       */
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
	introduce_champions(&cor);
	if (cor.visual_on == VISUAL_ON)
	{
		init_visu(&cor);
		create_color_panel();
		draw_starting_arena(&cor);
	}
	battle(&cor);
	announce_winner(&cor);
	if (cor.visual_on == VISUAL_ON)
	{
		endwin();
	}
	end(&cor);
}
