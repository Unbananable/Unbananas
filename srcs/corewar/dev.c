#include "corewar.h"

void	print_champ(t_champ *champ)
{
	unsigned int	i;

	printf("magic: %x\n", champ->head.magic);
	printf("prog name: %s\n", champ->head.prog_name);
	printf("prog size: %d\n", champ->head.prog_size);
	printf("comment: %s\n", champ->head.comment);
	printf("redcode:\n");
	i = 0;
	while (i < champ->head.prog_size)
	{
		printf("%.2x ", champ->redcode[i]);
		if (++i % 16 == 0)
			printf("\n");
	}
	if (i % 16 != 0)
		printf("\n");
}

void	print_cor(t_cor *cor)
{
	int		i;
	int		j;
	t_proc	*cache;

	printf("NUMBER OF CHAMPIONS: %d\n", cor->nb_champs);
	i = -1;
	while (++i < cor->nb_champs)
	{
		printf("\n==== CHAMPION %d ====\n", cor->champs[i]->player_no);
		print_champ(cor->champs[i]);
	}
	printf("\n==== ARENA ====\n");
	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			printf("%.2x ", cor->arena[i + j]);
			j ++;
		}
		printf("\n");
		i += j;
	}
	printf("\n==== PROCESSES ====\n");
	cache = cor->procs;
	j = 1;
	while (cache)
	{
		printf("%dth PROC:\n", j++);
		printf("\tproc id: %d\n", cache->n);
		printf("\tcarry: %d\n", cache->carry);
		printf("\tproc index in arena: %d\n", cache->idx);
		printf("\tregisters:\n");
		i = -1;
		while (++i < REG_NUMBER)
			printf("\t\t%d\t%.2x %.2x %.2x %.2x\n", i, cache->regs[i][0], cache->regs[i][1], cache->regs[i][2], cache->regs[i][3]);
		cache = cache->next;
	}
}
