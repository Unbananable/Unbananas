/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 14:58:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	t_cor	cor;

	// TO DO: Gestion des options
	ac--;
	av++;
	/*while (**av == '-')
		get_option(&ac, &av);*/

	initialize(&cor);

	// TO DO: Recuperer les champions
	get_champions(&cor, ac, av);
print_cor(&cor);

	// TO DO: Setup l'arene

	// TO DO: Suivi des commandes
}
