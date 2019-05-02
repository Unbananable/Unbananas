/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 13:22:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	usage(void)
{
	ft_putstr_fd("usage: ./corewar [-n player_number] champion.cor ...\n", 2);
}

int		main(int ac, char **av)
{
	t_cor	cor;

	// TO DO: Gestion des options

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
}
