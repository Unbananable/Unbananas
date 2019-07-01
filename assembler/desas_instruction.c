/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desas_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:31:50 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 23:01:32 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*add_token_operation_id(t_token *token, unsigned int id)
{
	if (id > 16)
		exit_msg("pb add_token_operation_id\n");
	token->value.operation = &g_op_tab[id];
	return (token);
}


int		get_param(t_champion *champion, char param, unsigned char *prog, int pos)
{
	t_token *token;
	int size;
	int value;

	if (param == REG_CODE || param == T_REG)
		token = create_token(champion, 0 , REGISTER);
	else if (param == DIR_CODE || param == T_DIR)
		token = create_token(champion, 0 , DIRECT);
	else if (param == IND_CODE || param == T_IND)
		token = create_token(champion, 0 , INDIRECT);
	else
		return (0x0);
	if (token->type == DIRECT && !(prog[0] > 8 && prog[0] < 16 && prog[0] != 13))
		size = 4;
	else if (token->type == REGISTER)
		size = 1;
	else
		size = 2;
	ft_memcpy(&value, &prog[pos], size);
	value = convert_bigendian(value, size);
	add_token_integer(token, value);
	add_token(token, champion);
	affichetype(token->type);
	ft_printf("== %hd\n", value);
	return (size);
}
int		get_instruction(t_champion *champion, unsigned char *prog)
{
	t_token	*token;
	int pos;
	char param[3] = {0,0,0};
	int i;

	i = -1;
	pos = 1;
	if (prog[0] > 16 && prog[0] > 0)
		return (0);
	token = create_token(champion, 0, INSTRUCTION);
	add_token_operation_id(token, prog[0] - 1);
	add_token(token, champion);
	ft_printf("INSTRUCTION %s\n", token->value.operation->operation);
	if (!(prog[0] == 1 || prog[0] == 9 || prog[0] == 12 || prog[0] == 15))
	{
		pos++;
		param[0] = (prog[1] & 192) >> 6;
		param[1] = (prog[1] & 46) >> 4;
		param[2] = (prog[1] & 12) >> 2;
		while (param[++i])
			pos += get_param(champion, param[i], prog, pos);
	}
	else
		while (++i < token->value.operation->number_param)
			pos += get_param(champion, token->value.operation->tab[i],
					prog, pos);

	return (pos);
}
