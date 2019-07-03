/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:29:46 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 17:42:23 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		firstcheck(t_fichier **file, char *s)
{
	int				len;

	len = ft_strlen(s);
	if (len > 2 && s[len - 2] == '.' && s[len - 1] == 's')
		if (((*file)->fd_in = open(s, O_RDONLY)) != -1)
		{
			(*file)->file_name = ft_strnjoin(s, "9.cor", ft_strlen(s) - 2);
			return (1);
		}
	return (0);
}

static int		main_champion(t_champion *champion, t_fichier *file, char *name)
{
	if (!firstcheck(&file, name))
		return (0);
	if (!parsing(file, champion))
		return (0);
	return (1);
}

int				main(int argc, char **argv)
{
	t_champion		*champion;
	t_fichier		*file;
	int i;

	i = 0;
	if(!(champion = init_champion()) || !(file = init_file()))
		return (0);
	while (++i < argc)
		main_champion(champion, file, argv[i]);
	return (0);
}
