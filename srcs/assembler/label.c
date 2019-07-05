/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:51:05 by abossard          #+#    #+#             */
/*   Updated: 2019/07/02 18:40:55 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_label(t_champion *champion, char *str)
{
	int i;

	i = -1;
	while (++i < champion->number_labels)
		if (!ft_strcmp(str, champion->tokens[champion->labels[i]]->value.data))
			return (champion->labels[i]);
	return (-1);
}

int		already_label(t_champion *champion, char *str, int pos)
{
	int i;

	i = -1;
	while (++i < champion->number_labels)
		if (!ft_strcmp(str, champion->tokens[champion->labels[i]]->value.data)
			&& champion->labels[i] != pos)
			return (1);
	return (0);
}

void	check_label(t_champion *c, t_token *t, int pos, int nb)
{
	t_token *next;

	next = c->tokens[pos + 1];
	if (!next || (next->type != INSTRUCTION && next->type != LABEL))
		error_champion(c, "Instruction or label not found", t->line);
	else if (already_label(c, t->value.data, pos))
		error_champion(c, "Label already exists", t->line);
	else
	{
		if (next->line == t->line)
			check_instruction(c, next, pos + 1, nb - 1);
	}
}

int		manage_label_param(t_champion *champion, char *str)
{
	int position_label;
	int val;

	if ((position_label = find_label(champion, str)) == -1)
		return (error_champion(champion, "Label does not exist", -1));
	val = champion->tokens[position_label]->pos;
	return (champion->instructions[val]);
}