/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fillers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:21:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 18:36:49 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fill_register()
{
}

void	fill_hex(t_cor *cor, int addr, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		cor->hex[i] = cor->arena[(addr + i) % MEM_SIZE];
	cor->hex[size] = '\0';
}

int get_reg_value() {}