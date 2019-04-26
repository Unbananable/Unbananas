#include "corewar.h"

void	print_init_arena(t_cor *cor)
{
	int		i;
	int		i_champ;
	int		current;

	if (!cor->arena)
		return ;
	current = 0;
	i_champ = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (current && current % 30 == 0)
			printf("\n");
		if (i == 0 || cor->arena[i - 1] == 0)
		{
			if (i_champ == 0)
				printf("\033[0;30m");
			else if (i_champ == 1)
				printf("\033[0;31m");
			else if (i_champ == 2)
				printf("\033[0;32m");
			else
				printf("\033[0;33m");
			i_champ++;
		}
		if (cor->arena[i] == 0)
			printf("\033[0m");
		printf("%.2x ", cor->arena[i]);
		current++;
	}
	printf("\n");
}
