/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fillers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:21:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/14 16:29:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	get_reg_value(unsigned char *reg)
{
	int		i;
	int		res;

	i = 3;
	res = reg[3];
	while (--i >= 0)
		res = res * 256 + reg[i];
	return (res);
}

int	restricted_addr(int new_idx)
{
	if (new_idx < 0)
		return (MEM_SIZE + (new_idx % MEM_SIZE));
	else
		return (new_idx % MEM_SIZE);
}
