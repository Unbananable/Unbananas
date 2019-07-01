/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champion_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 23:03:42 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 23:17:58 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void		write_line_token(t_token *token)
{


}

int			write_champion_prog(t_champion *champion, char *str)
{
	int fd;
	int i;

	i = -1;
	str = ft_strnjoin(str, "s2", ft_strlen(str) - 3);
	fd = open(str, O_WRONLY | O_CREAT);
	ft_memdel((void**)&str);
	ft_putstr_fd(NAME_CMD_STRING,fd);
	ft_putstr_fd(" \"",fd);
	ft_putstr_fd(champion->header->prog_name,fd);
	ft_putstr_fd("\"\n",fd);
	ft_putstr_fd(COMMENT_CMD_STRING,fd);
	ft_putstr_fd(" \"",fd);
	ft_putstr_fd(champion->header->comment, fd);
	ft_putstr_fd("\"\n",fd);
	while (++i < champion->number_token)
		write_line_token(champion->tokens[i]);
	close (fd);
	return (0);
}

