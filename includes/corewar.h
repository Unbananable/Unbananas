/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/03 17:08:35 by anleclab         ###   ########.fr       */
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

#define BYTE1 1
#define BYTES2 2
#define BYTES3 3
#define BYTES4 4
#define BYTES5 5
#define BYTES6 6
#define BYTES7 7

#define NB_OPERATIONS 16

typedef enum		e_bool
{
	false,
	true
}					t_bool;

/*
** OPERATION STRUCTURE:
** - name: nom de l'operation
** - nb_args: nombre d'arguments que prend l'operation
** - args : liste contenant les types d'arguments acceptable pour chaque
**          argument
** - opcode: code de l'operation
** - wait: nombre de cycles d'attente avant execution de l'operation
** - full_name: nom etendu de l'operation
** - ?? //TO DO: identifier
** - ?? //TO DO: identifier
*/

typedef struct		s_op
{
	char			*name;
	int				nb_args;
	t_arg_type		*args;
	unsigned char	opcode;
	unsigned int	wait;
	char			*full_name;
	/* ??? TO DO: identifier */
	/* ??? TO DO: identifier : taille du indirect ? */
	int				(*f)(t_cor *, t_proc *);
}					t_op;

/*
** CHAMPION STRUCTURE:
** - head: structure containing information about the champion (name, comment,
**         process size, etc. cf op.h)
** - player_no: player number
** - redcode: the champion's process code
** - curr_live: //TO DO
** - last_live: //TO DO
*/

typedef struct		s_champ
{
	header_t		head;
	int				player_no;
	unsigned char	*redcode;
	unsigned int	curr_live;
	unsigned int	last_live;
}					t_champ;

/*
typedef struct		s_option //TODO marqueurs des differentes options
{
	int				verbose; //TODO initialize apres parsing, prend une valeur, qui designe les donnees a afficher (cf resources/corewar)
}					t_option;
*/

/*
** PROCESS / CURSOR STRUCTURE (chained list):
** - n:	unique identification number: initialised at creation, never
**      changes
** - carry: flag: initialized at creation, changed by some operations
** - curr_opcode: op_code of the operation the proc is on: not initialised,
**                changed when the proc moves
** - last_live_cycle: last cycle the proc performed live: initialized to 0
**                    at creation, changed by live operation
** - wait: number of cycles before the operation is performed: not initialized,
**         decremented at each new cycle and reset when the proc moves
** - idx: current proc position: initialized at creation, changed everytime the
**        proc moves
** - move: length of the step to get to the next instruction: not initialized,
**         changed everytime the proc moves
** - regs: registers: initialized at creation, changed by some operations
** - next: next proc in the list
*/

typedef struct		s_proc
{
	int				n;
	t_bool			carry;
	unsigned char	curr_opcode;
	unsigned int	last_live_cycle;
	unsigned int	wait;
	unsigned int	idx;
	unsigned int	move;
	unsigned char	*(regs[REG_NUMBER]);
	struct s_proc	*next;
}					t_proc;

/*
** PROGRAM STRUCTURE:
** - nb_champs: number of champions
** - champs: list of champions (see champion structure)
** - arena: VM memory area
** - hex: //TO DO (string de taille REG_SIZE + 1 qui permettra de stocker les
**        infos a deplacer via les instructions, plus simple a utiliser que
**        char[5] a mon gout) TODO initialize char * (REG_SIZE + 1), puis bzero
** - procs: chained list of processes/cursors
** - curr_cycle: number of cycles since the beginning
** - curr_cycle_period: number of cycles since the beginning of the new period
** - cycle_to_die: number of cycles in a period
** - nb_live: number of live instructions performed in the period
** - nb_checks: number of periods since the last period when the period was
**              last reduced
** - last_alive: player number of the last champion who performed the live
**               instruction
*/

typedef struct		s_cor
{
	int				nb_champs;
	t_champ			**champs;
	unsigned char	*arena;
	unsigned char	*hex; 
	t_proc			*procs;
/*	t_option		option;*/
	unsigned int	curr_cycle;
	unsigned int	curr_cycle_period;
	unsigned int	cycle_to_die;
	unsigned int	nb_live;
	unsigned int	nb_checks;
	int				last_alive;
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

void			battle(t_cor *cor);

//void			fill_register(t_cor *cor, char reg_id, char *content);
//int			restricted_addr(t_cor *cor, unsigned int proc_id, int addr);
//int			cyd_val(int value);

//void			instr_live(t_cor *cor, unsigned int proc_id);
//void			instr_ld(t_cor *cor, unsigned int proc_id);
//void			instr_st(t_cor *cor, unsigned int proc_id);

t_proc			*new_proc(void);
t_proc			*add_proc(t_proc *new, t_proc *list);
void			delete_procs(t_proc **procs);

void			memcpy_big(void *dst, void *src, size_t size);

void			end(t_cor *cor);
void			error(t_cor *cor, char *err_type);
void			delete_champion(t_champ **champ);

/* DEV */
void		print_cor(t_cor *cor);

#endif
