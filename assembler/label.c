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
		error_champion(c, "instruction or label not found", t->line);
	else if (already_label(c, t->value.data, pos))
		error_champion(c, "label already exist", t->line);
	else
	{
		//t->param[0] = next;
		if (next->line == t->line)
			check_instruction(c, next, pos + 1, nb - 1);
	}
}

int		manage_label_param(t_champion *champion, char *str)
{
	int position_label;
	int val;

	if ((position_label = find_label(champion, str)) == -1)
		return (error_champion(champion, "label don't exist", -1));
	val = champion->tokens[position_label]->pos;
	return (champion->instructions[val]);
}
