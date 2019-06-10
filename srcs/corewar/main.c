/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 13:45:48 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	usage(void)
{
	ft_putstr_fd("usage: ./corewar [-dump nbr_cycles] [[-n player_number] ", 2);
	ft_putstr_fd("champion1.cor] ...\n", 2);
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
	get_dump_info(&cor, &ac, &av);
	get_champions(&cor, ac, av);
	order_champions(&cor);
	arena_setup(&cor);
print_cor(&cor);
	
	introduce_champions(&cor);
	battle(&cor);
	announce_winner(&cor);
	end(&cor);
}
