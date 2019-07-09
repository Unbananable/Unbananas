/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:04:22 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/09 19:16:01 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void		delete_token(t_token *token)
{
	int t;

	t = token->type;
	token->type = EMPTY;
	if (t == STRING)
		ft_memdel((void**)(&token->value.data));
}

int			search_label(t_champion *c, char *s)
{
	int i;

	i = -1;
	while (++i < c->number_token)
		if (c->tokens[i]->type == LABEL &&
				!ft_strcmp(c->tokens[i]->value.data, s))
			return (i);
	return (-1);
}

int			verify_champion(t_champion *c)
{
	int i;
	int l;
	int j;

	i = 0;
	while (i < c->number_token)
	{
		while (i < c->number_token && c->tokens[i] &&
			c->tokens[i]->type == EMPTY)
			i++;
		if (i == c->number_token)
			break ;
		l = c->tokens[i]->line;
		j = i;
		while (j < c->number_token && c->tokens[j] && c->tokens[j]->line == l)
			j++;
		verify_champion_line(c, c->tokens[i]->type, i, j - i);
		i = j;
		if (c->number_error > NUMBERMAX_ERROR)
			return (-1);
	}
	if (!c->hasname || !c->hascomment)
		warning_champion(c, "missing name or comment", -1);
	return ((c->number_error || !c->hasname || !c->hascomment) ? -1 : 1);
}
