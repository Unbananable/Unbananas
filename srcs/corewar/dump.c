/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:00:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/12 13:19:45 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_addr(int addr)
{
	int		i;
	char	*hex;

	ft_putstr("0x");
	hex = ft_itoa_base(addr, 16);
	i = 5;
	while (--i > (int)ft_strlen(hex))
		ft_putchar('0');
	ft_putstr(hex);
	free(hex);
	ft_putstr(" : ");
}

void		dump(t_cor *cor)
{
	int		i;
	int		j;
	char	*bytes;

/*ft_putstr("\n============= DUMP =============\n\n");
ft_putstr("cycle_to_die: ");
ft_putnbr(cor->cycle_to_die);
ft_putstr("\nnbr_live: ");
ft_putnbr(cor->nb_live);
ft_putstr("\n\n");
ft_putstr("** Champions **\n");
i = -1;
while (++i < cor->nb_champs)
{
	ft_putstr(cor->champs[i]->head.prog_name);
	ft_putstr(": last live = ");
	ft_putnbr(cor->champs[i]->last_live);
	ft_putstr(", lives_in_curr_period = ");
	ft_putnbr(cor->champs[i]->lives_in_curr_period);
	ft_putstr("\n");
}
ft_putstr("\n");
t_proc *cache;
cache = cor->procs;
int nb_procs = 0;
while (cache)
{
ft_putstr("Proc: idx = ");
ft_putnbr(cache->idx);
ft_putstr(", wait = ");
ft_putnbr(cache->wait);
ft_putstr(", move = ");
ft_putnbr(cache->move);
ft_putstr("\n\n");
cache = cache->next;
nb_procs++;
}
ft_putstr("nb_procs = ");
ft_putnbr(nb_procs);
ft_putstr("\n\n");*/

	i = 0;
	while (i < MEM_SIZE)
	{
		print_addr(i);
		j = 0;
		while (j < 64) // [TO DO] Repasser à 32 après les tests
		{
			/*cache = cor->procs;
			while (cache){
				if ((unsigned int)(i + j) == cache->idx)
					ft_putstr("\033[0;31m");
				cache = cache->next;
			}*/
			bytes = ft_itoa_base(cor->arena[i + j], 16); // [IMPROVE] Faire une fonction pour ne pas passer par un malloc
			if (ft_strlen(bytes) == 1)
				ft_putchar('0');
			ft_putstr(bytes);
			free(bytes);
			ft_putchar(' ');
			j++;
			//ft_putstr("\033[0;m");
		}
		ft_putchar('\n');
		i += j;
	}
	end(cor);
}
