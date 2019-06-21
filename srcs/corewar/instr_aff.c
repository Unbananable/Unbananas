/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:08:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 11:36:09 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** AFF
** - opcode: 0x0F
** - wait: 2
** - argcode: yes
** - args: REG
** - addressing retriction: no
** - carry: 1 if the content of the argument is 0, 1 otherwise
** - description: Displays the character corresponding to the argument (mod 256)
*/

void		instr_aff(t_cor *cor, t_proc *proc)
{
	char	tmp;

	if (get_args(cor, proc))
	{
		proc->carry = !cor->args[0].val;
		tmp = (char)(cor->args[0].val % 255);
		write(1, &tmp, 1);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | aff %d\n", proc->n, cor->args[0].val);
	}
}
