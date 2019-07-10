/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:49:18 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/09 22:16:04 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
 *	Ce fichier sert exclusivement de test il ne sera pas rendu 
 */

int		afficheLabels(t_champion *champion)
{
	int i;
	t_token *token;

	i = -1;
	while (++i < champion->number_labels)
	{
		token = champion->tokens[champion->labels[i]];
		ft_printf("label %d: %s pos: %d\n",
		i, token->value.data, champion->labels[i]);
	}
	return (1);
}

int	affichetype(int type)
{
	//ft_printf("type == ");
	if (type == LABEL)
		ft_printf("LABEL ");
	else if (type == INSTRUCTION)
		ft_printf("INSTRUCTION ");
	else if (type == REGISTER)
		ft_printf("REGISTER ");
	else if (type == SEPARATOR)
		ft_printf("SEPARATOR ");
	else if (type == NAME)
		ft_printf("NAME ");
	else if (type == COMMENT)
		ft_printf("COMMENT ");
	else if (type == DIRECT_LABEL || type == DIRECT_LABEL_STR)
		ft_printf("DIRECT_LABEL ");
	else if (type == DIRECT)
		ft_printf("DIRECT ");
	else if (type == INDIRECT_LABEL || type == INDIRECT_LABEL_STR)
		ft_printf("INDIRECT_LABEL ");
	else if (type == INDIRECT)
		ft_printf("INDIRECT ");
	else if (type == STRING)
		ft_printf("STRING ");
	else if (type == UNKNOWN)
		ft_printf("UNKNOWN ");
	else if (type == EMPTY)
		ft_printf(" _ ");
	else
		 return (ft_printf("IMPOSSIBLE ") + 5);
	return (0);
}

void		affiche_parametre(t_token *token)
{
	if (token->type == REGISTER)
		ft_printf("registre_%d", token->value.number);
	else if (token->type == INDIRECT)
		ft_printf("ind_%d", token->value.number);
	else if (token->type == DIRECT)
		ft_printf("dir_%d", token->value.number);
	else if (token->type == INDIRECT_LABEL)
		ft_printf("ind_label_", token->value.data);
	else if (token->type == DIRECT_LABEL)
		ft_printf("dir_label_", token->value.data);
	else
	{
		ft_printf("probleme ligne %d", token->line);
		affichetype(token->type);
	}
}

int			afficheInstruction(t_token *token, t_op *inst, int mode)
{
	if (mode == MODEREEL)
		ft_printf(inst->operation);
	if (token->param[0])
	{
		ft_printf("(");
		if (mode == MODETOKEN)
			affichetype(token->param[0]->type);
		else
			affiche_parametre(token->param[0]);
		if (token->param[1])
		{
			ft_printf(", ");
			if (mode == MODETOKEN)
				affichetype(token->param[1]->type);
			else
				affiche_parametre(token->param[1]);
		}
		if (token->param[2])
		{
			ft_printf(", ");
			if (mode == MODETOKEN)
				affichetype(token->param[2]->type);
			else
				affiche_parametre(token->param[2]);
		}
		ft_printf(")");
	}
	return (1);
}

int			test_champion(t_champion *champion, int mode)
{
	int i;
	int line = 0;
	int t;
	t_token *token;

	i = -1;
	while (++i < champion->number_token)
	{
		while (i < champion->number_token && champion->tokens[i]->type == EMPTY)
			i++;
		if (i == champion->number_token)
			break;
		token = champion->tokens[i];
		if (!token)
		{
			ft_printf("probleme test_champion!"); // test.c
			exit(1);
		}
		while (line < token->line)
		{
			ft_printf("\nline%d:", line);
			line++;
		}
		t = token->type;
		if (mode == MODETOKEN)
		{
			affichetype(t);
		}
		else
		{
		if (t == LABEL || t == DIRECT_LABEL ||
			t == INDIRECT_LABEL || t == STRING || t == UNKNOWN)
			ft_printf("%s ", token->value.data);
		else if (t == REGISTER || t == DIRECT || t == INDIRECT)
			ft_printf("%d ", token->value.number);
		}
		if (t == INSTRUCTION)
			afficheInstruction(token, token->value.operation, mode);
	}
	ft_printf("\n nom du champion: %s\n", champion->header->prog_name);
	ft_printf("comment champion: %s\n", champion->header->comment);
	ft_printf("j'ai trouve %d erreurs et %d avertissements\n",
			champion->number_error, champion->number_warning);
	return (1);
}

