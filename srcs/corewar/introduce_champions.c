/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:17:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/03 17:45:02 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce_champions(t_cor *cor)
{
	int		i;

	ft_putendl("Introducing contestants...");
	i = -1;
	while (++i < cor->nb_champs)
	{
		ft_putstr("* Player ");
		ft_putnbr(i + 1);
		ft_putstr(", weighing ");
		ft_putnbr(cor->champs[i]->head.prog_size);
		ft_putstr(" bytes, \"");
		ft_putstr(cor->champs[i]->head.prog_name);
		ft_putstr("\" (\"");
		ft_putstr(cor->champs[i]->head.comment);
		ft_putendl("\")!");
	}
}
