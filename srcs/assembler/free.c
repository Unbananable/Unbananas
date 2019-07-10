/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:22:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/10 11:59:15 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	delete_token(t_token *token)
{
	int t;

	t = token->type;
	token->type = EMPTY;
	if (t == STRING)
		ft_memdel((void**)(&token->value.data));
}

void	free_token(t_token **token)
{
	int t;

	if (*token)
	{
		t = (*token)->type;
		free_token(&(*token)->param[0]);
		free_token(&(*token)->param[1]);
		free_token(&(*token)->param[2]);
		if (t == STRING || t == LABEL || t == DIRECT_LABEL_STR ||
				t == INDIRECT_LABEL_STR)
			ft_memdel((void**)&(*token)->value.data);
		ft_memdel((void**)token);
	}
}

void	free_champion(t_champion **champion)
{
	int i;

	if (*champion)
	{
		i = -1;
		while (++i < (*champion)->number_token)
			if ((*champion)->tokens[i])
				free_token(&(*champion)->tokens[i]);
		ft_memdel((void**)(&(*champion)->tokens));
		ft_memdel((void**)(&(*champion)->header));
		ft_memdel((void**)(champion));
		*champion = 0x0;
	}
}

void	free_file(t_fichier **file)
{
	if (*file)
	{
		ft_strdel(&(*file)->file_name);
		ft_memdel((void**)file);
		*file = 0x0;
	}
}
