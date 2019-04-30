/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:03:03 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 15:01:39 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	delete_champion(t_champ **champ)
{
	if (*champ)
		free((*champ)->instr);
	free(*champ);
	*champ = NULL;
}

void	end(t_cor *cor)
{
	int		i;

	if (cor->champs)
	{
		i = -1;
		while (cor->champs[++i])
			delete_champion(cor->champs);
	}
	free(cor->champs);
	free(cor->arena);
	exit(0);
}

void	error(t_cor *cor, char *err_type)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(err_type, 2);
	end(cor);
}
