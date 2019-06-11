/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:44:14 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/11 15:07:01 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	mapcpy(t_cor *cor, unsigned int idx, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
		cor->arena[restricted_addr(idx + i)] = ((unsigned char *)content)[i];
}

void	regcpy(unsigned char *reg, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
		reg[i] = ((unsigned char *)content)[i];
}
