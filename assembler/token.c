/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:03:47 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 16:34:12 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/*
 ** on part du principe que operation existe
 */
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
	token->param[0] = 0x0;
	token->param[1] = 0x0;
	token->param[2] = 0x0;
	return (token);
}

static	int		get_last_intruction_id(t_champion *champion)
{
	int id;
	int i;

	i = champion->number_token;
	while (--i >= 0 && champion->tokens[i]->type != INSTRUCTION)
		;
	id = (i < 0) ? -1 : champion->tokens[i]->value.operation->id;
	return (id);
}

/*
**	en cad de pb return 10
*/

int			size_token(int t, int id)
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
		res = (id == 1 || id == 9 || id == 12) ? 1 : 2;
	if (t == DIRECT || t == DIRECT_LABEL)
	{
		if (id < 0)
			return (10); // il y'a forcement une erreurs
		res = (id > 8 && id < 16 && id != 13) ? 2 : 4;
	}
	return (res);
}

void		add_token(t_token *token, t_champion *champion)
{
	if (token->type == INSTRUCTION)
	{
		champion->instructions[champion->number_instructions++] = champion->size;
		champion->size += size_token(token->type, token->value.operation->id);
	}
	else
		champion->size += size_token(token->type, get_last_intruction_id(champion));
	if (token->type == LABEL)
	{
		if (champion->number_labels >= BUFFER_LABELS - 1)
			exit_msg("fatal error to much labels");
		champion->labels[champion->number_labels] = champion->number_token;
		champion->number_labels++;
	}
	if (champion->number_token % BUFFER_TOKENS == BUFFER_TOKENS -1)
	{
		champion->tokens = realloc(champion->tokens,
		(champion->number_token + BUFFER_TOKENS + 1) * sizeof(t_token*));
	}
	champion->tokens[champion->number_token] = token;
	champion->number_token++;
}
