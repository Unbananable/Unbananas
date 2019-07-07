/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:48:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/07 22:28:19 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		ft_printf("String is too big or does not end: %d", line_nb);
		return (0x0);
	}
}

char			*string_exeption(t_fichier *file, char *line)
{
	int		line_nb;
	char	*s;
	char	*tmp;

	s = ft_strnew(1);
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

static int		is_end_word(char c)
{
	if (c == '"' || c == COMMENT_CHAR || c == SEPARATOR_CHAR || c == ';')
		return (1);
	return (0);
}

static int		end_word(char *s, int start)
{
	if (!s[start])
		return (start);
	while (s[start] && !(is_end_word(s[start]) || ft_isspace(s[start])))
		start++;
	return (start);
}



static t_token *analyse_element(t_champion *champion, char **line, t_fichier *file)
{
	t_token *token;
	int end;


	if (**line == COMMENT_CHAR || **line == ';')
		return (0x0);
	else if (**line == SEPARATOR_CHAR)
	{
		*line += 1;
		token = create_token(champion, file->line_nb, SEPARATOR);
	}
	else
	{
		end = end_word(*line, 0);
		token = get_token(champion, *line, end, file->line_nb);
		*line += end;
	}
	return (token);
}


static t_token *analyse_string(t_champion *champion, char **line, t_fichier *file)
{
	int		end;
	char	*tmp;
	int		actual;
	t_token *token;

	actual = file->line_nb;
	token = create_token(champion, actual, STRING);
	tmp = string_exeption(file, *line);
	token = add_token_string(token, tmp);
	ft_strdel(&tmp);
	if (actual != file->line_nb)
		ft_printf("String too long ?");
	*line = (actual < file->line_nb) ? file->line : *line;
	end = ft_strchr(*line, '"') - *line + 1;
	*line += end;
	return (token);
}

static void		analyse_line(t_fichier *file, char *line, t_champion *champion)
{
	t_token	*token;

	while (*line && ft_isspace(*line))
		line++;
	while (*line)
	{
		if (*line == '"')
		{
			line++;
			token = analyse_string(champion, &line, file);
		}
		else
		{
			token = analyse_element(champion, &line, file);
			if (!token)
				break;
		}
		add_token(token, champion);
		while (*line && ft_isspace(*line))
			line++;
	}
}

int				parsing(t_fichier *f, t_champion *champion)
{
	while (get_next_line(f->fd_in, &f->line) > 0)
	{
		analyse_line(f, f->line, champion);
		ft_strdel(&f->line);
		f->line_nb++;
	}
	ft_strdel(&f->line);
	verify_champion(champion);
	if (champion->number_error == 0)
		return (create_champion(f, champion));
	return (0);
}
