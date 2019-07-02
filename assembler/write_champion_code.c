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


void		write_line_token(t_token *token, int fd)
{
	int i = -1;
	int id;
	char *tmp;
	char tab[1000];

	ft_bzero(tab, 1000);
	ft_strcat(tab, token->value.operation->operation);
	ft_strcat(tab, "\t");
	id = token->value.operation->id;
	while (++i < token->value.operation->number_param)
	{
		if (token->param[i]->type == REGISTER)
			ft_strcat(tab, "r");
		else if (token->param[i]->type == DIRECT)
			ft_strcat(tab, "%");
		//cast la valeur puis ft_itoa +> strcat > si i < lim = strcat(,) 
//tmp = ft_itoa()
		//ft_(token->param[i]->value.number, )



	}


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
		write_line_token(champion->tokens[i], fd);
	close (fd);
	return (0);
}

