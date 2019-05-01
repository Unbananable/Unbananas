/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/01 17:53:42 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"

#include <stdio.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define CYCLE_LIVE 10
#define CYCLE_LD 5
#define CYCLE_ST 25

#define BYTE1 1
#define BYTES2 2
#define BYTES3 3
#define BYTES4 4
#define BYTES5 5
#define BYTES6 6
#define BYTES7 7

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef struct		s_champ
{
	header_t		head;
	int				player_no;
	unsigned char	*redcode;
	unsigned int	curr_live; //TODO initialize at start after parsing
	unsigned int	last_live; //TODO initialize at start after parsing
}					t_champ;
/*
typedef struct		s_option //TODO marqueurs des differentes options
{
	int				verbose; //TODO initialize apres parsing, prend une valeur, qui designe les donnees a afficher (cf resources/corewar)
}					t_option;
*/
typedef struct		s_proc
{
	int				n; //unique identification number: initialised at creation, never changes
	t_bool			carry; //flag: initialized at creation, changed by some operations
	unsigned char	curr_opcode; //op_code of the operation the proc is on: not initialised, changed when the proc moves
	unsigned int	last_live_cycle; //last cycle the proc performed live: initialized to 0 at creation, changed by live operation
	unsigned int	wait; //number of cycles before the operation is performed: not initialized, decremented at each new cycle and reset when the proc moves
	unsigned int	idx; //current proc position: initialized at creation, changed everytime the proc moves
	unsigned int	move; //length of the step to get to the next instruction: not initialized, changed everytime the proc moves
	unsigned char	regs[REG_NUMBER][REG_SIZE]; //registers: initialized at creation, changed by some operations
	s_proc			*next; //next proc in the list;
}					t_proc;

typedef struct		s_cor
{
	unsigned char	**reg; // (register) TODO initialize the 16 possible registers (4 uchar each, plus terminating '\0')
	unsigned char	*hex; // (string de taille REG_SIZE + 1 qui permettra de stocker les infos a deplacer via les instructions, plus simple a utiliser que char[5] a mon gout) TODO initialize char * (REG_SIZE + 1), puis bzero
	t_proc			*procs; // TODO initialize after parsing, realloc after a fork/lfork
	t_option		option;
	int				nb_champs;
	t_champ			**champs;
	unsigned char	*arena;
	unsigned int	curr_cycle; //TODO initialize at start after parsing
	t_bool			last_alive; //TODO initialize
}					t_cor;

void			initialize(t_cor *cor);

//void			fill_register(t_cor *cor, char reg_id, char *content);

//int			instr_live(t_cor *cor, unsigned int proc_id);
//void			instr_ld(t_cor *cor, unsigned int proc_id);
//void			instr_st(t_cor *cor, unsigned int proc_id);

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
