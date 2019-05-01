/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/01 11:24:50 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"

#include <stdio.h>

#define CYCLE_LIVE 10

typedef enum		e_bool
{
	true,
	false
}					t_bool;

typedef struct		s_champ
{
	header_t		head;
	int				player_no;
	unsigned char	*redcode;
	unsigned int	curr_live; //TODO initialize at start after parsing
	unsigned int	last_live; //TODO initialize at start after parsing
}					t_champ;

typedef struct		s_option //TODO marqueurs des differentes options
{
	int				verbose; //TODO initialize apres parsing, prend une valeur, qui designe les donnees a afficher (cf resources/corewar)
}					t_option;

typedef struct		s_proc
{
	unsigned int	id; //TODO initialize a la creation d un proc (numero d identification du processus)
	t_bool			carry; // TODO initialize a la creation d un proc
	unsigned int	cooldown; // TODO initialize a la creation d un proc
	unsigned int	idx; //TODO initialize a la creation d un proc (position dans l arene pour surbrillance)
}					t_proc;

typedef struct		s_cor
{
	t_proc			*procs; // TODO initialize after parsing, realloc after a fork/lfork
	t_option		option;
	int				nb_champs;
	t_champ			**champs;
	unsigned char	*arena;
	unsigned int	curr_cycle; //TODO initialize at start after parsing
	t_bool			last_alive; //TODO initialize
}					t_cor;

void			initialize(t_cor *cor);

//int			instr_live(t_cor *cor, int idx);

void			end(t_cor *cor);
void			error(t_cor *cor, char *err_type);
void			delete_champion(t_champ **champ);

void			get_champions(t_cor *cor, int ac, char **av);
unsigned int	get_magic(int fd);
int				get_prog_name(t_champ *champ, int fd);
unsigned int	get_prog_size(int fd);
int				get_comment(t_champ *champ, int fd);
unsigned char	*get_redcode(int fd, unsigned int size);

void			order_champions(t_cor *cor);

void			arena_setup(t_cor *cor);

/* DEV */
void		print_cor(t_cor *cor);

#endif
