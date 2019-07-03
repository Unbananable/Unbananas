/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:51:12 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 20:29:24 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


t_champion			*clear_champion(t_champion *champion)
{
	int i;

	i = -1;
	while (++i < (champion)->number_token)
		if ((champion)->tokens[i])
			free_token(&(champion)->tokens[i]);
	ft_bzero(champion->tokens, sizeof(t_token) * (CHAMP_MAX_SIZE * 2));
	champion->hasname = 0;
	champion->hascomment = 0;
	champion->number_token = 0;
	champion->number_error = 0;
	champion->number_warning = 0;
	champion->number_instructions = 0;
	champion->size = 0;
	champion->number_labels = 0;
	champion->header->prog_size = 0;
	champion->header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(champion->header->prog_name, PROG_NAME_LENGTH + 4);
	ft_bzero(champion->header->comment, PROG_NAME_LENGTH + 4);
	return (champion);
}

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
	clear_champion(champion);
	return (champion);
}
t_fichier			*clear_file(t_fichier *file)
{
	if (!file->file_name)
		ft_strdel(&file->file_name);
	file->fd_out = -1;
	file->line = 0x0;
	file->line_nb = 1;
	return (file);
}

t_fichier			*init_file()
{
	t_fichier *file;

	if (!(file = (t_fichier*)ft_memalloc(sizeof(t_fichier))))
		malloc_error("init_fichier");
	clear_file(file);
	return (file);
}
