/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/03 17:16:23 by dtrigalo         ###   ########.fr       */
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
#define CYCLE_ADD 10
#define CYCLE_SUB 10
#define CYCLE_AND 6
#define CYCLE_OR 6
#define CYCLE_XOR 6
#define CYCLE_ZJMP 20
#define CYCLE_LDI 25

#define FIRST_PARAM 1
#define SECOND_PARAM 2
#define THIRD_PARAM 3

#define NULL_CODE 4

#define OPC_BYTE 1
#define ARGC_BYTE 1
#define REG_BYTE 1
#define IND_BYTE 2
#define D2_BYTE 2
#define D4_BYTE 4

#define BYTE_SIZE 8
#define BIT 1

#define BYTE1 1
#define BYTES2 2
#define BYTES3 3
#define BYTES4 4
#define BYTES5 5
#define BYTES6 6
#define BYTES7 7
#define BYTES8 8
#define BYTES9 9
#define BYTES10 10
#define BYTES11 11

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
	unsigned char	*(regs[REG_NUMBER]); //registers: initialized at creation, changed by some operations
	struct s_proc	*next; //next proc in the list;
}					t_proc;

typedef struct		s_cor
{
	int				nb_champs;
	t_champ			**champs;
	unsigned char	*arena;
	unsigned char	*hex; // (string de taille REG_SIZE + 1 qui permettra de stocker les infos a deplacer via les instructions, plus simple a utiliser que char[REG_SIZE + 1] a mon gout) TODO initialize char * (REG_SIZE + 1), puis bzero
	t_proc			*procs; // TODO initialize after parsing
/*	t_option		option;*/
	unsigned int	curr_cycle; //TO DO initialize at start after parsing
	int				last_alive; //player_no of the last champion for whom live was performed
}					t_cor;

void			initialize(t_cor *cor);

void			get_champions(t_cor *cor, int ac, char **av);
unsigned int	get_magic(int fd);
int				get_prog_name(t_champ *champ, int fd);
unsigned int	get_prog_size(int fd);
int				get_comment(t_champ *champ, int fd);
unsigned char	*get_redcode(int fd, unsigned int size);

void			order_champions(t_cor *cor);

void			arena_setup(t_cor *cor);

//void			fill_register(t_cor *cor, char reg_id, char *content);
//int			restricted_addr(unsigned int program_counter, int addr);
//int			cyd_val(int value);
//int			bits_peer_type(t_cor *cor, t_proc *proc, int param_idx);

//int			instr_live(t_cor *cor, t_proc *proc);
//int			instr_ld(t_cor *cor, t_proc *proc);
//int			instr_st(t_cor *cor, t_proc *proc);
//int			instr_add(t_cor *cor, t_proc *proc);
//int			instr_sub(t_cor *cor, t_proc *proc);
//int			instr_or(t_cor *cor, t_proc *proc);
//int			instr_and(t_cor *cor, t_proc *proc);
//int			instr_xor(t_cor *cor, t_proc *proc);
//int			instr_zjmp(t_cor *cor, t_proc *proc);

t_proc			*new_proc(void);
t_proc			*add_proc(t_proc *new, t_proc *list);

void			memcpy_big(void *dst, void *src, size_t size);

void			end(t_cor *cor);
void			error(t_cor *cor, char *err_type);
void			delete_champion(t_champ **champ);

/* DEV */
void		print_cor(t_cor *cor);

#endif
