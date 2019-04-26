/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:59:59 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 17:08:31 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	initialize(t_cor *cor)
{
	cor->champs = NULL;
	if (!(cor->arena = (char *)malloc(sizeof(char) * MEM_SIZE)))
		error(cor, "malloc failed");
	ft_bzero(cor->arena, sizeof(char) * MEM_SIZE);
}
