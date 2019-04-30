/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:10:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 20:17:38 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				init_champs(t_cor *cor, int ac)
{
	int		i;

	if ((cor->nb_champs = ac) > MAX_PLAYERS)
		error(cor, "too many players");
	if (!(cor->champs = (unsigned char **)malloc(sizeof(unsigned char *)
			* (ac + 1))))
		error(cor, "malloc failed");
	i = -1;
	while (++i <= ac)
		cor->champs[i] = NULL;
}

/* FIX ME : Il reste un peu de merde en debut de chaine */
static unsigned char	*read_champion(char *str)
{
	int						fd;
	unsigned char			*champ;
	char					c;
	int						rval;
	unsigned long long int	i;
	char					name_comment[PROG_NAME_LENGTH + COMMENT_LENGTH];

	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	if (!(champ = (unsigned char *)malloc(sizeof(unsigned char)
					* (CHAMP_MAX_SIZE + 1))))
		return (NULL);
	read(fd, name_comment, PROG_NAME_LENGTH + COMMENT_LENGTH);
	i = 0;
	while ((rval = read(fd, &c, 1)) > 0 && i < CHAMP_MAX_SIZE)
		champ[i++] = (unsigned char)c;
	if (i == CHAMP_MAX_SIZE && rval > 0)
	{
		free(champ);
		return (NULL);
	}
	while (++i <= CHAMP_MAX_SIZE)
		champ[i] = 0;
	close(fd);
	return (champ);
}

void					get_champions(t_cor *cor, int ac, char **av)
{
	int		i;

	init_champs(cor, ac);

	i = -1;
	while (++i < cor->nb_champs)
		if (!(cor->champs[i] = read_champion(av[i])))
		{
			while (--i >= 0)
				free(cor->champs[i]);
			free(cor->champs);
			cor->champs = NULL;
			error(cor, "invalid champion");
		}

	i = -1;
	while (++i < cor->nb_champs)
		ft_memcpy(cor->arena + sizeof(char) * MEM_SIZE * i / cor->nb_champs,
				cor->champs[i], sizeof(char) * CHAMP_MAX_SIZE);
}
