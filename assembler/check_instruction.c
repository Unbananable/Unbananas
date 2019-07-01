/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:33:31 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 16:34:56 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


static int		isgoodparam(t_champion *c, t_token *token, int expected)
{
	int type;
	int tmp;

	type = token->type;
	if ((type == DIRECT_LABEL || type == INDIRECT_LABEL))
	{
		tmp = manage_label_param(c, token->value.data);
		ft_memdel((void**)&token->value.data);
		(tmp == -1) ? error_champion(c, "label no found", token->line) :
		token->value.number = tmp;
	}
	if (type == REGISTER && expected & T_REG)
		return (1);
	if ((type == DIRECT_LABEL || type == DIRECT) && expected & T_DIR)
		return (1);
	if ((type == INDIRECT_LABEL || type == INDIRECT) && expected & T_IND)
		return (1);
		ft_printf("mauvais parametre %s\n", token->value.data);
	return (0);
}

static int		manage_instruction(t_champion *c, t_op *inst, t_token *token, int pos)
{
	move_token(&token->param[0], &c->tokens[pos + 1]);
	if (inst->number_param > 1)
	{
		delete_token(c->tokens[pos + 2]);
		move_token(&token->param[1], &c->tokens[pos + 3]);
	}
	if (inst->number_param > 2)
	{
		delete_token(c->tokens[pos + 4]);
		move_token(&token->param[2], &c->tokens[pos + 5]);
	}
	return (1);
}

int		check_instruction(t_champion *c, t_token *token, int pos, int tok_line)
{
	t_op	*instruction;
	int i;

	instruction = token->value.operation;
	if (tok_line >= instruction->number_param * 2)
	{
		i = -1;
		while (++i < instruction->number_param)
		{
			if (!isgoodparam(c, c->tokens[pos + 2 * i + 1], instruction->tab[i]))
				return error_champion(c, "bad parameters", token->line);
			if (i < instruction->number_param - 1 &&
			c->tokens[pos + 2 * i + 2]->type != SEPARATOR)
				return error_champion(c, "separator expected", token->line);
		}
		if (tok_line > instruction->number_param * 2)
			return (error_champion(c, "trop d'elements", token->line));
		manage_instruction(c, instruction, token, pos);
		return (2 * i);
	}
	error_champion(c, "missing parameters", token->line);
	return (3);
}
