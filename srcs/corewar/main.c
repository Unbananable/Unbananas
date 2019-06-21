/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 14:21:46 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	usage(void)
{
	ft_putstr_fd("usage: ./corewar [-visual | [-v verbosity_level] ", 2);
	ft_putstr_fd("[-dump nbr_cycles]] [-n player_number] champion1.cor", 2);
	ft_putstr_fd(" ...\n\n*** VERBOSITY LEVEL ***\n 1: Live instructions\n", 2);
	ft_putstr_fd(" 2: Display current cycle and cycle to die decrement\n", 2);
	ft_putstr_fd(" 4: Display details of the instrutions\n 8: Display ", 2);
	ft_putstr_fd("carriage deaths\n16: Display movement of the PCs ", 2);
	ft_putstr_fd("(except in case of zjump)\nAdd the numbers for a ", 2);
	ft_putstr_fd("combination of verbosity levels\n", 2);
}

int		main(int ac, char **av)
{
	t_cor	cor;

	ac--;
	av++;
	if (!ac)
	{
		usage();
		return (0);
	}
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
	if (cor.visual_on)
	{
		init_visu(&cor);
		create_color_panel();
		draw_starting_arena(&cor);
	}
	battle(&cor);
	announce_winner(&cor);
	if (cor.visual_on)
	{
		wgetch(cor.visu->arena);
		wgetch(cor.visu->arena_info);
		endwin();
	}
	end(&cor);
}
