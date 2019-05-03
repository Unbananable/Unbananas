/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/03 10:24:24 by anleclab         ###   ########.fr       */
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

	// TO DO: Gestion de l'option -dump (+visu ?)

	ac--;
	av++;
	if (!ac)
		usage();
	initialize(&cor);
	get_champions(&cor, ac, av);
	order_champions(&cor);
	arena_setup(&cor);
print_cor(&cor);
	
	// TO DO: Introduire les champions

	// TO DO: Lancer le jeu [WIP anleclab]
	battle(&cor);

	// To DO: Annoncer le gagnant
}
