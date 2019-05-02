/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:59:59 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 13:57:10 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Initializes the t_cor structure.
*/

void	initialize(t_cor *cor)
{
	cor->champs = NULL;
	if (!(cor->arena = (unsigned char *)malloc(sizeof(unsigned char)
			* MEM_SIZE)))
		error(cor, "malloc failed");
	ft_bzero(cor->arena, sizeof(unsigned char) * MEM_SIZE);
	cor->hex = NULL;
	cor->procs = NULL;
}
