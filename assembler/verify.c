/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:04:22 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/19 19:36:43 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	delete_token(t_token *token)
{
	int t;

	t = token->type;
	token->type = EMPTY;
	if (t == STRING)
		ft_memdel((void**)(&token->value.data));
}

int search_label(t_champion *c, char *s)
{
	int i;

	i = -1;
	while (++i < c->number_token)
		if (c->tokens[i]->type == LABEL &&
				!ft_strcmp(c->tokens[i]->value.data, s))
				return (i);
	return (-1);
}

// appeler seulement apres verify_champion CHANGER
static int		verify_labelparameter(t_champion *c)
{
	int i;
	int j;
	t_token *token;

	i = 0;
	while (i < c->number_token)
	{
		token = c->tokens[i];
		if (token->type == INSTRUCTION)
		{
			j = -1;
			while (++j < 3)
			{
				if (token->param[j] && (token->param[j]->type == DIRECT_LABEL ||
									token->param[j]->type == INDIRECT_LABEL))
					if (!search_label(c, token->param[j]->value.data))
					{
						ft_printf("fatal error line :%d label \"%s\" not found",
								token->line, token->param[j]->value.data);
						exit_msg (" bye\n");
					}
			}
		}
		i++;
	}
	return (1);
}

int		verify_champion(t_champion *c)
{
	int i;
	int l;
	int j;

	i = 0;
	while (i < c->number_token)
	{
		while (i < c->number_token && c->tokens[i] && c->tokens[i]->type == EMPTY)
			i++;
		if (i == c->number_token)
			break;
		if (!c->tokens[i])
			exit_msg("probleme champion!");
		l = c->tokens[i]->line;
		j = i;
		while (j < c->number_token && c->tokens[j] && c->tokens[j]->line == l)
			j++;
		verify_champion_line(c, c->tokens[i]->type, i, j - i);
		i = j;
		if (c->number_error > NUMBERMAX_ERROR)
			return (-1);
	}
	//verify_labelparameter(c);
	return ((c->number_error || !c->hasname || !c->hascomment) ? -1 : 1);
}
