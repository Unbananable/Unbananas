/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 14:35:21 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"

#include <stdio.h>

typedef struct		s_champ
{
	char			*desc; //TODO initialize at start during/before parsing
	char			*name; //TODO initialize at start during/before parsing
	unsigned int	*curr_lives; //TODO initialize at start after parsing
	unsigned int	*last_live; //TODO initialize at start after parsing
}					t_champ;

typedef struct		s_cor
{
	t_champ			champ;
	unsigned char	**champs;
	int				nb_champs;
	unsigned char	*arena;
	char			*hex;
	char			max_player;
	unsigned int	curr_cycle; //TODO initialize at start after parsing
}					t_cor;

void		initialize(t_cor *cor);

void		end(t_cor *cor);
void		error(t_cor *cor, char *err_type);

void		get_champions(t_cor *cor, int ac, char **av);

/* DEV */
void		print_init_arena(t_cor *cor);

#endif
