/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:10:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 16:36:29 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Allocates memory for the cor structure to store information about the
** champions.
*/

static void		init_champs(t_cor *cor, int ac)
{
	int		i;

	if ((cor->nb_champs = ac) > MAX_PLAYERS)
		error(cor, "too many players");
	if (!(cor->champs = (t_champ **)malloc(sizeof(t_champ *)
			* (ac + 1))))
		error(cor, "malloc failed");
	i = -1;
	while (++i <= ac)
		cor->champs[i] = NULL;
}

static int		skip_empty_bytes(int fd)
{
	unsigned char	buf[5];
	int				rval;

	if ((rval = read(fd, buf, 4)) != 4)
		return (-1);
	buf[rval] = 0;
	while (*buf)
		if ((*buf)++ != 0)
			return (-1);
	return (0);
}

/*
** From a filename, returns the t_champ containing the information about
** the champion
*/

static t_champ	*read_champion(char *str)
{
	t_champ			*champ;
	int				fd;

	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		return (NULL);
	champ->redcode = NULL;
	if ((champ->head.magic = get_magic(fd)) != COREWAR_EXEC_MAGIC
			|| get_prog_name(champ, fd) == -1 || skip_empty_bytes(fd) == -1) //FIX ME
		delete_champion(&champ);
	if (!champ || (champ->head.prog_size = get_prog_size(fd)) > CHAMP_MAX_SIZE
			|| get_comment(champ, fd) == -1 || skip_empty_bytes(fd) == -1)
		delete_champion(&champ);
	if (!champ || !(champ->redcode = get_instr(fd, champ->head.prog_size)))
		delete_champion(&champ);
	if (close(fd) == -1)
		delete_champion(&champ);
	return (champ);
}

/*
** For all parameters of the corewar program, get the information contained in
** the files for the champions.
** TO DO : Take options into account.
*/

void			get_champions(t_cor *cor, int ac, char **av)
{
	int		i;

	init_champs(cor, ac);
	i = -1;
	while (++i < cor->nb_champs)
		if (!(cor->champs[i] = read_champion(av[i])))
		{
			while (--i >= 0)
				delete_champion(&(cor->champs[i]));
			free(cor->champs);
			cor->champs = NULL;
			error(cor, "invalid champion");
		}
}
