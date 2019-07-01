/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:22:02 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 22:56:02 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_strnjoin(char *s1, char *s2, int size)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(size + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strncpy(str, s1, size);
	ft_strcat(str, s2);
	return (str);
}

long long		convert_bigendian(long long val, unsigned int size)
{
	int		i;
	int		len;
	long	long unsigned res;
	int		base;

	if (size == 1)
		return (val);
	if (size > sizeof(long long) || !size || size % 2)
		return (0);
	i = -1;
	len = (size - 1) * 8;
	res = 0;
	base = 0x000000ff;
	while (++i < size)
	{
		if (len > 0)
			res += (base & val) << len;
		else
			res += (base & val) >> (-len);
			len -= 16;
		base <<= 8;
	}
	return (res);
}

int			write_header(header_t *header, int fd)
{
	char		buff[SIZEMAX_STRING + 4];
	int tmp;

	tmp = convert_bigendian( header->magic, 4);
	write(fd, &tmp, 4);
	ft_putstr_fd(header->prog_name , fd);
	ft_bzero(buff, SIZEMAX_STRING + 4);
	tmp = PROG_NAME_LENGTH - ft_strlen(header->prog_name);
	write(fd, buff, tmp + 4);
	tmp = convert_bigendian(header->prog_size, 4);
	write(fd, &tmp, 4);
	ft_putstr_fd(header->comment , fd);
	tmp = COMMENT_LENGTH - ft_strlen(header->comment);
	write(fd, buff, tmp + 4);
	return (1);
}

static unsigned char opcode(t_token *token)
{
	unsigned char	res;
	int				i;
	int				decalage;
	int				tmp;


	i = -1;
	decalage = 6;
	res = 0;
	while (++i < token->value.operation->number_param)
	{
		tmp = token->param[i]->type;
		if (tmp == REGISTER)
			res += 1 << decalage;
		else if (tmp == DIRECT || tmp == DIRECT_LABEL)
			res += 2 << decalage;
		else if (tmp == INDIRECT || tmp == INDIRECT_LABEL)
			res += 3 << decalage;
		decalage -= 2;
	}
	return (res);
}


int		convert_param_hexa(t_champion *c, t_token *token, int start, int id)
{
	int res;
	int type;
	int label;

	res = 0;
	type = token->type;
	if (type != REGISTER)
	{
		if((type == DIRECT || type == DIRECT_LABEL) &&
		!(id > 8 && id < 16 && id != 13))
		{
			c->prog[start + ++res] = (token->value.number & 0xff000000) >> 24;
			c->prog[start + ++res] = (token->value.number & 0x00ff0000) >> 16;
		}
		c->prog[start + ++res] = (token->value.number & 0x0000ff00) >> 8;
	}
	c->prog[start + ++res] = token->value.number & 0x000000ff;
	return (res);
}

int		convert_token_hexa(t_champion *c, int start, t_token *token)
{
	int res;
	int id;
	int i;
	t_token *tmp;

	res = -1;
	id = token->value.operation->id;
	c->prog[start + ++res] = id;
	if (!(id == 1 || id == 9 || id == 12 || id == 15))
		c->prog[start + ++res] = opcode(token);
	i = -1;
	while (++i < token->value.operation->number_param)
	{
		if (token->param[i]->type == DIRECT_LABEL ||
				token->param[i]->type == INDIRECT_LABEL)
			token->param[i]->value.number -= start;
res += convert_param_hexa(c, token->param[i], start + res, token->value.operation->id);
	}
	return (res + 1);
}

int			manage_prog(t_champion *champion)
{
	int i;
	int tok;

	i = 0;
	tok = -1;
	while (++tok < champion->number_token)
	{
		while (tok < champion->number_token &&
				champion->tokens[tok]->type != INSTRUCTION)
			tok++;
		if (tok < champion->number_token)
			i += convert_token_hexa(champion, i, champion->tokens[tok]);
	}
	return (i);
}

int			create_champion(t_fichier *file, t_champion *champion)
{
	int size;

	//test_champion(champion, MODEREEL);
	file->fd_out = open(file->file_name, O_WRONLY | O_CREAT);
	champion->header->prog_size = champion->size;
	write_header(champion->header, file->fd_out);
	ft_printf("je dois creer mon champion\n\n\n");
	size = manage_prog(champion);
	write(file->fd_out, champion->prog, size);
	close(file->fd_out);

	/*afficheLabels(champion);
	ft_printf("nb magic %u\n", 0xff000000,champion->header->magic%256);
	ft_printf("prog_name %s\n", champion->header->prog_name);
	ft_printf("comment %s\n", champion->header->comment);
	ft_printf("size champion %u\n", champion->size);
	ft_printf("file: %s\n", file->file_name);
	*/
	return (1);
}
