/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:27:11 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/19 10:48:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_dump_info(t_cor *cor, int *ac, char ***av)
{
	int		i;

	if (*ac >= 2)
	{
		i = -1;
		while ((*av)[1][++i])
			if ((*av)[1][i] > '9' || (*av)[1][i] < '0') // [IMPROVE] Verifier aussi que le nombre est un unsigned int
				return (ERROR);
		cor->dump = 1;
		cor->dump_cycle = ft_atoi((*av)[1]); // [IMPROVE] atoi d'un unsigned int
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR);    
}

static int  get_verbose_info(t_cor *cor, int *ac, char ***av)
{
	int		i;

	if (*ac >= 2)
	{
		i = -1;
		while ((*av)[1][++i])
			if ((*av)[1][i] > '9' || (*av)[1][i] < '0') // [IMPROVE] Verifier aussi que le nombre est un char (meme inferieur a 0b00111111)
				return (ERROR);
		cor->verbose = (char)ft_atoi((*av)[1]);
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR); 
}

int         get_options(t_cor *cor, int *ac, char ***av)
{
	while ((*av)[0][0] == '-')
	{
		if (ft_strequ((*av)[0], "-dump"))
		{
			if (get_dump_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-v"))
		{
			if (get_verbose_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-n"))
			break ;
		else if (ft_strequ((*av)[0], "-visual"))
		{
			cor->visual_on = VISUAL_ON;
			(*av)++;
			(*ac)--;
		}
		else
			return (ERROR);
	}
	return (0);
}
