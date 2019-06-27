/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:22:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/27 19:23:51 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void		free_token(t_token **token)
{
	int t;
	if (*token)
	{
		t = (*token)->type;
		if (t != LABEL)
			free_token(&(*token)->param[0]);
		free_token(&(*token)->param[1]);
		free_token(&(*token)->param[2]);
	 if (/*t == DIRECT_LABEL || t == INDIRECT_LABEL ||*/t == STRING)
			ft_memdel((void**)&(*token)->value.data);
		ft_memdel((void**)token);
//		 *token = 0x0;
	}
}


void		free_champion(t_champion **champion)
{
	int i;

	if (*champion)
	{
		i = -1;
		while (++i < (*champion)->number_token)
			if ((*champion)->tokens[i])
				free_token(&(*champion)->tokens[i]);
		//ft_printf("%d\n",i);}
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
