/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_procs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:38:34 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 13:52:12 by anleclab         ###   ########.fr       */
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

void	delete_procs(t_proc **procs)
{
	t_proc	*cache;
	int		i;

	while (*procs)
	{
		cache = (*procs)->next;
		i = -1;
		while (++i < REG_NUMBER)
			free(regs[i]);
		free(*procs);
		*procs = cache;
	}
}
