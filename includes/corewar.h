/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/26 17:40:29 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

typedef struct		s_cor
{
	char	**champs;
	int		nb_champs;
	char	*arena;
}					t_cor;

void		initialize(t_cor *cor);

void		end(t_cor *cor);
void		error(t_cor *cor, char *err_type);

#endif
