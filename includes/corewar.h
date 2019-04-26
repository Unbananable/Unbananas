/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 18:51:59 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"

#include <stdio.h>

typedef struct		s_cor
{
	unsigned char	**champs;
	int		nb_champs;
	unsigned char	*arena;
}					t_cor;

void		initialize(t_cor *cor);

void		end(t_cor *cor);
void		error(t_cor *cor, char *err_type);

void		get_champions(t_cor *cor, int ac, char **av);

/* DEV */
void		print_init_arena(t_cor *cor);

#endif
