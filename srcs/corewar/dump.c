/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:00:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 11:29:16 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    dump(t_cor *cor)
{
    int     i;
	int		j;
    char    *bytes;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 32)
		{
            bytes = ft_itoa_base(cor->arena[i + j], 16);
            if (ft_strlen(bytes) == 1)
                ft_putchar('0');
			ft_putstr(bytes);
            if (j < 31)
                ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i += j;
	}
    end(cor);
}