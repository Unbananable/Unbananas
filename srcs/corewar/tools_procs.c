/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_procs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:38:34 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/14 16:03:25 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc	*new_proc(void)
{
	t_proc	*new;
	int		i;

	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	i = -1;
	while (++i < REG_NUMBER)
	{
		if (!(new->regs[i] = (unsigned char *)malloc(sizeof(unsigned char)
						* REG_SIZE)))
		{
			while (--i >= 0)
				free(new->regs[i]);
			free(new);
			return (NULL);
		}
		ft_bzero(new->regs[i], sizeof(char) * REG_SIZE);
	}
	new->next = NULL;
	return (new);
}

t_proc	*add_proc(t_proc *new, t_proc *list)
{
	new->next = list;
	return (new);
}

void	delete_proc(t_proc **proc)
{
	int		i;

	i = -1;
	while (++i < REG_NUMBER)
		free((*proc)->regs[i]);
	free(*proc);
	*proc = NULL;
}

void	delete_procs(t_proc **procs)
{
	t_proc	*cache;

	while (*procs)
	{
		cache = (*procs)->next;
		delete_proc(procs);
		*procs = cache;
	}
}

t_proc	*clone_proc(t_cor *cor, t_proc *original)
{
	t_proc	*new;
	int		i;

	new = new_proc();
	cor->nb_procs++;
	new->n = cor->new_proc_n++;
	new->carry = original->carry;
	new->last_live_cycle = original->last_live_cycle;
	i = -1;
	while (++i < REG_NUMBER)
		ft_memcpy(new->regs[i], original->regs[i], REG_SIZE);
	return (new);
}
