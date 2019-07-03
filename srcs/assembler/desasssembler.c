/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desasssembler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:09:00 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/03 21:58:08 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			read_champion(t_champion *champion, int fd)
{
	int		i;
	int		n;
	int		tmp;

	i = 0;
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
	return (1);
}

int			read_header(t_champion *champion, int fd)
{
	int			n;
	int			size;
	t_header	*header;
	char		tab[4];

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
	return (1);
}

static int	main_unasm(t_champion *champion, char *name)
{
	int fd;
	int size;

	size = ft_strlen(name);
	if (size > 5 && !ft_strcmp(&name[size - 4], ".cor"))
		fd  = (open(name, O_RDONLY));
	else
		fd = -1;
	champion = clear_champion(champion);
	if (fd == -1)
	{
		ft_printf("probleme nom du fichier");
		return (0);
	}
	if (read_header(champion, fd) && read_champion(champion, fd))
		return (write_champion_prog(champion, name));
	return (0);
}

int			main(int argc, char *argv[])
{
	t_champion	*champion;
	int i;

		champion = init_champion();
	i = 0;
	while (++i < argc)
		if (main_unasm(champion, argv[i]))
			ft_printf("Writing output program to %s\n", argv[i]);
		else
			ft_printf("IMPOSSIBLE: %s\n", argv[i]);
	free_champion(&champion);
	return (0);
}
