#include "asm.h"


int	read_champion(t_champion *champion, int fd)
{
	int i;

	i = -1;
	while (++i < champion->header)
	return(0);
}

int write_champion_prog(t_champion *champion, char *str)
{
	return (0);
}

int		read_header(t_champion *champion, int fd)
{
	int n;
	int size;
	header_t *header;

	header = champion->header;
	size = 12 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	n = read(fd, header, size);
	if (n < size)
		return (0);
	if (convert_bigendian(header->magic, 4) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("probleme nombre magic\n");
		return (0);
	}
	header->prog_size = convert_bigendian(header->prog_size);
	return (0);
}

int		open_champion(char *str)
{
	int size;

	size = ft_strlen(str);
	if (size > 5 && !ft_strcmp(&str[size - 4], ".cor"))
		return (open(str, O_RDONLY));
	return (-1);
}

int main(int argc, char *argv[])
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
	return 0;
}

