/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:14:48 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/09 13:39:07 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

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

t_token		*add_token_operation(t_token *token, char *s)
{
	int i;

	i = 0;
	while (op_tab[i].operation && ft_strcmp(op_tab[i].operation, s))
		i++;
	if (!op_tab[i].operation)
		return (0x0);
	token->value.operation = &op_tab[i];
	return (token);
}
