/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:29:46 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/27 19:29:48 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		firstcheck(int argc, char **argv)
{
	int		len;
	char	*s;

	if (argc == 1)
	{
		return (0);
	}
	else if (argc > 2)
	{
		return (0);
	}
	s = argv[1];
	len = ft_strlen(s);
	if (len > 2 && s[len - 2] == '.' && s[len - 1] == 's')
		return (1);
	return (0);
}

static char		*join_norme(char *s, char *line, int line_nb)
{
	char *res;


	if (ft_strlen(s) + ft_strlen(line) < COMMENT_LENGTH + PROG_NAME_LENGTH)
	{
		res = ft_strjoin(s, line);
		free(s);
		return (res);
	}
	else
	{
		ft_printf("chaine trop grande ou non fermé %d", line_nb);
		return (0x0);
	}
}

char			*string_exeption(t_fichier *file, char *line)
{
	int line_nb;
	char *s = ft_strnew(1);
	char *tmp;

	line_nb = file->line_nb;
	while (!(tmp = ft_strchr(line, '"')) && file->line)
	{
		if (!(s = join_norme(s, line, line_nb)))
			return (0x0);
		ft_strdel(&file->line);
		get_next_line(file->fd_in, &file->line);
		ft_printf("\n");
		line = file->line;
		file->line_nb++;
	}
	*tmp = '\0';
	if (!(s = join_norme(s, line, line_nb)))
		return (0x0);
	*tmp = '"';
	return (s);
}

int			main(int argc, char **argv)
{
	t_champion			*champion;
	t_fichier				*file;

	if (!firstcheck(argc, argv))
		return (0);
	champion = init_champion();
	if (!(file = init_file(argv[1])))
		return (0);
	if (!parsing(file, champion))
		return (0);
	return (0);
}
