/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:10:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 17:43:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		init_champs(t_cor *cor, int ac)
{
	int		i;

	if ((cor->nb_champs = ac) > MAX_PLAYERS)
		error(cor, "too many players");
	if (!(cor->champs = (char **)malloc(sizeof(char *) * ac)))
		error(cor, "malloc failed");
	i = -1;
	while (++i <= ac)
		cor->champs[i] = NULL;
}

char	*read_champion(char *str)
{
	t_stream	*stream;
	char		*champ;
	int			i;
	char		rval;

	if (!(stream = ft_fopen(str)))
		return (NULL);
	if (!(champ = (char *)malloc(sizeof(char) * (CHAMP_MAX_SIZE + 1))))
		return (NULL);
	rval = 1;
	i = -1;
	while ((rval = ft_fgetc(stream)) >= 0 && ++i < CHAMP_MAX_SIZE)
		champ[i] = rval;
	while (++i <= CHAMP_MAX_SIZE)
		champ[i] = 0;
	ft_fclose(*stream);
	return (champ);
}

void	get_champions(t_cor *cor, int ac, char *av)
{
	int		i;

	init_champs(cor, ac);

	i = -1;
	while (++i < cor->nb_champs)
		if (!(champs[i] = read_champion(av[i])))
		{
			while (--i >= 0)
				free(cor->champs[i]);
			free(cor->champs);
			cor->champs = NULL;
			error(cor, "invalid champion");
		}

	i = -1;
	while (++i < cor->nb_champions)
		ft_memcpy(cor->arena + sizeof(char) * MEM_SIZE * i / cor->nb_champions,
				cor->champs[i], sizeof(char) * CHAMP_MAX_SIZE);
}
