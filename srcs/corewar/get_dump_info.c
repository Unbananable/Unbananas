/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dump_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:37:44 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 13:47:27 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    get_dump_info(t_cor *cor, int *ac, char ***av)
{
    int     i;

    if (*ac >= 2 && ft_strequ(**av, "-dump"))
    {
        i = -1;
        while ((*av)[1][++i])
            if ((*av)[1][i] > '9' || (*av)[1][i] < '0') // [IMPROVE] Verifier aussi que le nombre est un unsigned int
            {
                ft_putendl("Invalid dump option, ignoring...");
                (*av)++;
                (*ac)--;
                return;
            }
        cor->dump = 1;
        cor->dump_cycle = ft_atoi((*av)[1]); // [IMPROVE] atoi d'un unsigned int
        (*av) += 2;
        (*ac) -= 2;
    }
}