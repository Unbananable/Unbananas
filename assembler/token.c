/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:03:47 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/17 18:14:42 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
extern t_op g_op_tab[17];

t_token		*add_token_operation(t_token *token, char *s)
{
	int i;

	i = 0;
	while (g_op_tab[i].operation && ft_strcmp(g_op_tab[i].operation, s))
		i++;
	if (!g_op_tab[i].operation)
		exit_msg("pb add_token_operation");
	token->value.operation = &g_op_tab[i];
	return (token);
}

t_token		*add_token_string(t_token *token, char *str)
{
	token->value.data = ft_strdup(str);
	//ft_printf("(%s)", token->value.data);
	return (token);
}

t_token		*add_token_integer(t_token *token, int value)
{
	token->value.number = value;
	return (token);
}

t_token *create_token(t_champion *c, int line_nb, int type)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	token->line = line_nb;
	token->type = type;
	token->param[0] = 0;
	token->param[1] = 0;
	token->param[2] = 0;
	return (token);
}

static	t_token	*get_last_intruction(t_champion *champion)
{
	t_token *t;
	int i;

	i = champion->number_token;
	while (--i > 0 && champion->tokens[i]->type != INSTRUCTION)
		;
	t = (champion->tokens[i]->type != INSTRUCTION) ? 0x0 : champion->tokens[i];
	return (t);
}

/*
**	en cad de pb return 10
*/

int			size_token(t_token *token, int t, t_champion *champion)
{
	int		res;
	int		tmp;

	res = 0;
	if (t == UNKNOWN)
		res = 10;
	if (t == REGISTER)
		res = 1;
	if (t == INDIRECT || t == INDIRECT_LABEL)
		res = 2;
	if (t == INSTRUCTION)
	{
		tmp = token->value.operation->id;
		res = (tmp == 1 || tmp == 9 || tmp == 12) ? 1 : 2;
	}
	if (t == DIRECT || t == DIRECT_LABEL)
	{
		if (!(token = get_last_intruction(champion)))
			return (10); // il y'a forcement une erreurs
		tmp = token->value.operation->id;
		res = (tmp > 8 && tmp < 16 && tmp != 13) ? 2 : 4;
	}
	return (res);
}

void		add_token(t_token *token, t_champion *champion)
{
	if (token->type == INSTRUCTION)
		champion->instructions[champion->number_instructions++] = champion->size;
	if (token->type == LABEL)
	{
		if (champion->number_labels >= BUFFER_LABELS - 1)
			exit_msg("fatal error to much labels");
		champion->labels[champion->number_labels] = champion->number_token;
		champion->number_labels++;
	}
	champion->size += size_token(token, token->type, champion);
	if (champion->number_token % BUFFER_TOKENS == BUFFER_TOKENS -1)
	{
		champion->tokens = realloc(champion->tokens,
		(champion->number_token + BUFFER_TOKENS + 1) * sizeof(t_token*));
	}
	champion->tokens[champion->number_token] = token;
	champion->number_token++;
}
