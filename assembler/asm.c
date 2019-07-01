/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:29:46 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 16:52:50 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		firstcheck(int argc, char **argv)
{
	int				len;
	char			*s;

	if (argc == 1)
		return (0);
	else if (argc > 2)
		return (0);
	s = argv[1];
	len = ft_strlen(s);
	if (len > 2 && s[len - 2] == '.' && s[len - 1] == 's')
		return (1);
	return (0);
}

int				main(int argc, char **argv)
{
	t_champion		*champion;
	t_fichier		*file;

	if (!firstcheck(argc, argv))
		return (0);
	champion = init_champion();
	if (!(file = init_file(argv[1])))
		return (0);
	if (!parsing(file, champion))
		return (0);
	return (0);
}
