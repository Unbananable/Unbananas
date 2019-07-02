/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desasssembler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:09:00 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 22:28:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"





int			read_champion(t_champion *champion, int fd)
{
	int i;
	int n;
	int tmp;

	i = 0;
	ft_printf("read_champion %d /%d\n", champion->header->prog_size, CHAMP_MAX_SIZE);
	n = read(fd, champion->prog, champion->header->prog_size + 1);
	if (n != champion->header->prog_size)
	{
		ft_printf("bad size %d /%d\n", n, champion->header->prog_size);
		return (0);
	}
	while (i < champion->header->prog_size)
	{
		if ((tmp = get_instruction(champion, &champion->prog[i])))
			i += tmp;
		else
			return (0);
	}
	ft_printf("=============\n\n\n");
	//test_champion(champion, MODEREEL);
	return(1);
}

int			read_header(t_champion *champion, int fd)
{
	int n;
	int size;
	header_t *header;
	char	tab[4];

	ft_printf("read_header\n");
	header = champion->header;
	size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	n = read(fd, header, size);
	if (n < size)
		return (0);
	if (convert_bigendian(header->magic, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("probleme nombre magic\n");
		return (0);
	}
	header->prog_size = convert_bigendian(header->prog_size, 4);
	//read(fd, tab, 4);
	return (1);
}

static int	open_champion(char *str)
{
	int size;

	size = ft_strlen(str);
	if (size > 5 && !ft_strcmp(&str[size - 4], ".cor"))
		return (open(str, O_RDONLY));
	return (-1);
}

int			main(int argc, char *argv[])
{
	int fd;
	t_champion *champion;

	if (argc != 2)
		return (0);

	fd = open_champion(argv[1]);
	if (fd == -1)
	{
		ft_printf("probleme nom du fichier");
		return (-1);
	}
	champion = init_champion();
	if (read_header(champion, fd))
		if (read_champion(champion, fd))
			write_champion_prog(champion, argv[1]);
	return (0);
}

