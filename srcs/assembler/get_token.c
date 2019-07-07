/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:51:33 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/07 20:06:13 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_isnumber(char *s)
{
	int size;

	size = 0;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		s++;
		size++;
	}
	if (size > 0 && !*s)
		return (1);
	return (0);
}

int			move_token(t_token **token, t_token **anc)
{
	*token = *anc;
	*anc = create_token(NULL, (*token)->line, EMPTY);
	return (1);
}

t_token		*get_direct_token(t_champion *c, int line, char *s)
{
	if (*s == DIRECT_CHAR)
	{
		s++;
		if (ft_isnumber(s))
			return (add_token_integer(create_token(c, line, DIRECT),
						ft_atoi(s)));
		if (*s == LABEL_CHAR)
		{
			s++;
			if (compose_withthese_letters(s, LABEL_CHARS))
				return (add_token_string(create_token(c, line, DIRECT_LABEL),
							s));
		}
	}
	ft_printf("probleme syntax incorrect pour un \"Direct\" %s", s);
	return (create_token(c, line, UNKNOWN));
}


t_token		*get_token_param(t_champion *c, char *s, int line_nb)
{
	t_token *token;


	if (ft_strchr(s, DIRECT_CHAR))
		token = get_direct_token(c, line_nb, s);
	else if (isregister(s))
		token = add_token_integer(create_token(c, line_nb, REGISTER),
				ft_atoi(&s[1]));
	else if (ft_isnumber(s))
		token = add_token_integer(create_token(c, line_nb, INDIRECT),
				ft_atoi(s));
	else if (isindirect_label(s))
		token = add_token_string(create_token(c, line_nb, INDIRECT_LABEL),
				&s[1]);
	else
	{
		token = create_token(c, line_nb, UNKNOWN);
		ft_printf("probleme syntax error %s", s);
	}
	return (token);
}


t_token		*get_token(t_champion *c, char *s, int end, int line_nb)
{
	t_token	*token;
	char	last_char;

	last_char = s[end];
	s[end] = '\0';
	if (!ft_strcmp(s, NAME_CMD_STRING))
		token = create_token(c, line_nb, NAME);
	else if (!ft_strcmp(s, COMMENT_CMD_STRING))
		token = create_token(c, line_nb, COMMENT);
	else if (islabel(s))
	{
		token = add_token_string(create_token(c, line_nb, LABEL), s);
		token->value.data[ft_strlen(s) - 1] = '\0';
		token->pos = c->number_instructions;
	}
	else if (isintruction(s))
		token = add_token_operation(create_token(c, line_nb, INSTRUCTION), s);
	else
		token = get_token_param(c, s, line_nb);
	s[end] = last_char;
	return (token);
}
