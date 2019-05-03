/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 10:26:55 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Takes a T_DIR(2) as parameter
*/

int		instr_zjmp(t_cor *cor, t_proc *proc)
{
	int		addr;
	int		i;

	i = -1;
	while (++i < DIR_SIZE / 2)
		cor->hex[i] = cor->arena[cyd_value(proc->idx + i)];
	addr = ft_uchar_to_short_base(cor->hex, 16);
	ft_bzero(cor->hex, DIR_SIZE / 2);
	if (!carry)
		proc->move = DIR_SIZE / 2 + BYTE1;
	else
		proc->move = restricted_addr(proc->idx, addr);
}
