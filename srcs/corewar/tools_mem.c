/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:44:14 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/18 12:02:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	mapcpy(t_cor *cor, unsigned int idx, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
		cor->arena[restricted_addr(idx + i)] = ((unsigned char *)content)[REG_SIZE - i - 1];
}

void	regcpy(unsigned char *reg, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
		reg[i] = ((unsigned char *)content)[i];
}
