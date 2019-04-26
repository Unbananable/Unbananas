/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:50:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 17:47:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int c, char **av)
{
	t_cor	cor;

	// TO DO: Gestion des options
	/*ac--;
	av++;
	while (**av == '-')
		get_option(&ac, &av);*/

	initialize(&cor);

	// TEST ME: Recuperer les champions
	get_champions(&cor, ac, av);

	// TO DO: Setup l'arene

	// TO DO: Suivi des commandes
}
