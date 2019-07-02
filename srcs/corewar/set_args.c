/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:53:20 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/02 10:53:22 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	t_arg(unsigned char argcode)
{
	if (argcode == REG_CODE)
		return (T_REG);
	else if (argcode == DIR_CODE)
		return (T_DIR);
	else if (argcode == IND_CODE)
		return (T_IND);
	return (0);
}

int				arg_length(unsigned char argtype, unsigned char opcode)
{
	if (argtype == T_REG)
		return (1);
	if (argtype == T_DIR)
	{
		if (opcode == FORK_CODE || opcode == LDI_CODE || opcode == LFORK_CODE
				|| opcode == LLD_CODE || opcode == LLDI_CODE
				|| opcode == STI_CODE || opcode == ZJMP_CODE)
			return (2);
		else
			return (4);
	}
	if (argtype == T_IND)
		return (2);
	return (0);
}

int				get_arg(t_cor *cor, t_proc *proc, unsigned char argtype,
		int arglength)
{
	int		arg;
	int		i;

	arg = cor->arena[restricted_addr(proc->idx)];
	i = 0;
	while (++i < arglength)
		arg = arg * 256 + cor->arena[restricted_addr(proc->idx + i)];
	return (arg);
}

t_bool			set_args(t_cor *cor, t_proc *proc, int opcode)
{
	int				i;
	unsigned char	argtype;
	unsigned char	argbits;
	int				arglength;
	t_bool			arg_ok;

	arg_ok = true;
	argbits = 0b11000000;
	proc->move = 2;
	i = -1;
	while (++i < op_code[opcode][ARG_NB])
	{
		argtype = t_arg((argbits & cor->arena[restricted_add(proc->idx
						+ 1)]) >> (6 - 2 * i));
		arglength = arg_length(argtype, opcode);
		if (argtype & op_code[opcode][ARG_TYPE][i])
			proc->args[i] = get_arg(cor, proc, argtype, arglength);
		else
			arg_ok = false;
		proc->move += arglength;
		argbits = argbits >> 2;
	}
	return (arg_ok);
}
