/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:51:12 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 16:16:17 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_champion			*init_champion(void)
{
	t_champion *champion;

	if (!(champion = (t_champion*)ft_memalloc(sizeof(t_champion))))
		malloc_error("init_champion");
	else if ((!(champion->header = (header_t*)ft_memalloc(sizeof(header_t))) ||
	!(champion->tokens = (t_token**)malloc(sizeof(t_token*) * BUFFER_TOKENS))))
	{
		if (champion->header)
			free(champion->header);
		free(champion);
		champion = 0X0;
		malloc_error("init_champion");
	}
	champion->hasname = 0;
	champion->hascomment = 0;
	champion->number_token = 0;
	champion->number_error = 0;
	champion->number_warning = 0;
	champion->number_instructions = 0;
	champion->size = 0;
	champion->number_labels = 0;
	champion->header->magic = COREWAR_EXEC_MAGIC;
	return (champion);
}

t_fichier			*init_file(char *str)
{
	t_fichier *file;

	if (!(file = (t_fichier*)malloc(sizeof(t_fichier))))
		malloc_error("init_fichier");
	if ((file->fd_in = open(str, O_RDONLY)) == -1)
		exit_msg("probleme open file (fichier non existant)\n");
	file->file_name = ft_strnjoin(str, "cor2", ft_strlen(str) - 1);
	file->fd_out = -1;
	file->line = 0x0;
	file->line_nb = 1;
	return (file);
}
