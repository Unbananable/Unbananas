#include "asm.h"


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
