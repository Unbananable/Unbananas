/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:00:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/11 16:11:30 by dtrigalo         ###   ########.fr       */
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

	ft_putstr("\n============= DUMP =============\n\n");
	t_proc *cache;
	cache = cor->procs;
	while (cache){
		ft_putstr("Proc: idx = ");
		ft_putnbr(cache->idx);
		ft_putstr(", wait = ");
		ft_putnbr(cache->wait);
		ft_putstr(", move = ");
		ft_putnbr(cache->move);
		ft_putstr("\n\n");
		cache = cache->next;}

	i = 0;
	while (i < MEM_SIZE)
	{
		print_addr(i);
		j = 0;
		while (j < 64) // [TO DO] Repasser à 32 après les tests
		{
			cache = cor->procs;
			while (cache){
				if ((unsigned int)(i + j) == cache->idx)
					ft_putstr("\033[0;31m");
				cache = cache->next;
			}
			bytes = ft_itoa_base(cor->arena[i + j], 16); // [IMPROVE] Faire une fonction pour ne pas passer par un malloc
			if (ft_strlen(bytes) == 1)
				ft_putchar('0');
			ft_putstr(bytes);
			free(bytes);
			/*if (j < 31)*/ // [TO DO] Decommenter;
			ft_putchar(' ');
			j++;
			ft_putstr("\033[0;m");
		}
		ft_putchar('\n');
		i += j;
	}
	end(cor);
}
