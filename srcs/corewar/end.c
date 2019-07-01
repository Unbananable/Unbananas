/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:03:03 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/01 16:53:38 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Frees a single champion
*/

void	delete_champion(t_champ **champ)
{
	if (*champ)
		free((*champ)->redcode);
	free(*champ);
	*champ = NULL;
}

/*
** Frees the whole t_cor structure.
*/

void	end(t_cor *cor)
{
	int		i;

	if (cor->champs)
	{
		i = -1;
		while (cor->champs[++i])
			delete_champion(&(cor->champs[i]));
	}
	free(cor->champs);
	free(cor->arena);
	delete_procs(&(cor->procs));
	if (cor->visual_on)
	{
		if (cor->visu->arena)
			delwin(cor->visu->arena);
		if (cor->visu->arena)
			delwin(cor->visu->arena_info);
		if (cor->visu->arena_period_bar)
			delwin(cor->visu->arena_period_bar);
		free(cor->visu);
	}
	exit(0);
}

/*
** Frees the whole cor structure, prints the given error message on the error
** output and exits the program.
*/

void	error(t_cor *cor, char *err_type)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(err_type, 2);
	end(cor);
}
