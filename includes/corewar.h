/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/20 16:16:08 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"
# include "ft_printf.h"

# include <stdio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define CYCLE_LIVE 10
# define CYCLE_LD 5
# define CYCLE_ST 25
# define CYCLE_ADD 10
# define CYCLE_SUB 10
# define CYCLE_AND 6
# define CYCLE_OR 6
# define CYCLE_XOR 6
# define CYCLE_ZJMP 20
# define CYCLE_LDI 25
# define CYCLE_STI 25
# define CYCLE_FORK 800
# define CYCLE_LLD 10
# define CYCLE_LFORK 1000
# define CYCLE_AFF 2

# define NB_OPERATIONS 16

# define ERROR -1

/*
** Byte representation of the verbose options
*/
# define V_LIVES 1
# define V_CYCLES 2
# define V_OPERATIONS 4
# define V_DEATHS 8
# define V_PROC 16

typedef enum		e_bool
{
	false,
	true
}					t_bool;

/*
** CHAMPION STRUCTURE:
** - head: structure containing information about the champion (name, comment,
**         process size, etc. cf op.h)
** - player_no: player number
** - redcode: the champion's process code
** - last_live: cycle in which the last live was performed for the champion
** - lives_in_curr_period: number of live operations performed for the champion
**   in the current period
*/

typedef struct		s_champ
{
	header_t		head;
	int				player_no;
	unsigned char	*redcode;
	unsigned int	last_live;
	unsigned int	lives_in_curr_period;
	unsigned int	lives_in_last_period;
}					t_champ;

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
	int				parent_id;
	t_bool			carry;
	unsigned char	opcode;
	unsigned int	last_live_cycle;
	unsigned int	wait;
	unsigned int	idx;
	int				move;
	unsigned char	*(regs[REG_NUMBER]);
	struct s_proc	*next;
}					t_proc;

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

struct				s_cor;

typedef struct		s_op
{
	char			*name;
	int				nb_args;
	int				args[3];
	unsigned char	opcode;
	unsigned int	wait;
	char			*full_name;
	void			(*f)(struct s_cor *, t_proc *);
	int				dir_size;
	int				ind_size;
}					t_op;

/*
** ARGUMENT STRUCTURE:
** - type: type of the argument. One of T_REG, T_DIR, T_IND or 0
** - val: value of the argumen. It corresponds to the value of the DIR, the
**   position relative to the proc index of a IND, or the register number
**   depending on the type of argument
*/

typedef struct		s_arg
{
	t_arg_type	type;
	int			val;
}					t_arg;

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
** - dump: 1 if the dump option was used, 0 otherwise
** - dump_cycle: number of the cycle at which the memory (arena) must be dumped
**               (only when dump is set to 1)
** - verbose: verbose level. Each bit represents an aspect of the verbosity.
*/

typedef struct		s_cor
{
	int				nb_champs;
	t_champ			**champs;
	unsigned char	*arena;
	t_proc			*procs;
	t_op			*op_tab;
	t_arg			args[3];
	unsigned int	curr_cycle;
	unsigned int	curr_cycle_period;
	int				cycle_to_die;
	unsigned int	nb_live;
	unsigned int	nb_checks;
	int				last_alive;
	int				dump;
	unsigned int	dump_cycle;
	char			verbose;
	unsigned int	nb_procs;
	unsigned int	new_proc_n;
	struct s_visu	*visu;
	t_bool			visual_on;
}					t_cor;

void			initialize(t_cor *cor);

int				get_options(t_cor *cor, int *ac, char ***av);

void			get_champions(t_cor *cor, int ac, char **av);
unsigned int	get_magic(int fd);
int				get_prog_name(t_champ *champ, int fd);
unsigned int	get_prog_size(int fd);
int				get_comment(t_champ *champ, int fd);
unsigned char	*get_redcode(int fd, unsigned int size);

void			order_champions(t_cor *cor);

void			arena_setup(t_cor *cor);

void			introduce_champions(t_cor *cor);

void			battle(t_cor *cor);

void			announce_winner(t_cor *cor);

void			instr_live(t_cor *cor, t_proc *proc);
void			instr_ld(t_cor *cor, t_proc *proc);
void			instr_st(t_cor *cor, t_proc *proc);
void			instr_add(t_cor *cor, t_proc *proc);
void			instr_sub(t_cor *cor, t_proc *proc);
void			instr_or(t_cor *cor, t_proc *proc);
void			instr_and(t_cor *cor, t_proc *proc);
void			instr_xor(t_cor *cor, t_proc *proc);
void			instr_zjmp(t_cor *cor, t_proc *proc);
void			instr_sti(t_cor *cor, t_proc *proc);
void			instr_ldi(t_cor *cor, t_proc *proc);
void			instr_lld(t_cor *cor, t_proc *proc);
void			instr_lldi(t_cor *cor, t_proc *proc);
void			instr_aff(t_cor *cor, t_proc *proc);
void			instr_fork(t_cor *cor, t_proc *proc);
void			instr_lfork(t_cor *cor, t_proc *proc);

int				get_arg_true_val(t_cor *cor, t_proc *proc, t_arg arg,
		t_bool addr_restriction);
int				get_args(t_cor *cor, t_proc *proc);
short			get_short_arg_value(t_cor *cor, int idx);
int				get_int_arg_value(t_cor *cor, int idx, int size);
int 			get_reg_value(unsigned char *reg);
int				restricted_addr(int new_idx);
void			mapcpy(t_cor *cor, t_proc *proc, unsigned int idx, void *content);
void			regcpy(unsigned char *reg, void *content);

t_proc			*new_proc(void);
t_proc			*add_proc(t_proc *new, t_proc *list);
void			delete_procs(t_proc **procs);
void			delete_proc(t_proc **proc);
t_proc 			*clone_proc(t_cor *cor, t_proc *original);

void    		dump(t_cor *cor);

void			end(t_cor *cor);
void			error(t_cor *cor, char *err_type);
void			delete_champion(t_champ **champ);

//# include "op.c"

/* DEV */
void		print_cor(t_cor *cor);

/* *** VISU *** */

# include <ncurses.h>

# define HEIGHT (MEM_SIZE / 64 + 4)
# define WIDTH ((MEM_SIZE / 64) * 3 + 5)

# define START_SPEED	50

# define LIVE_BRIGHT_TIME 50
# define STORE_BRIGHT_TIME 50

# define VISUAL_ON		true

# define RED			8
# define RED_CURSOR		9
# define RED_LIVE		10
# define GREEN			11
# define GREEN_CURSOR	12
# define GREEN_LIVE		13
# define YELLOW			14
# define YELLOW_CURSOR	15
# define YELLOW_LIVE	16
# define BLUE			17
# define BLUE_CURSOR	18
# define BLUE_LIVE		19
# define MAGENTA		20
# define MAGENTA_CURSOR	21
# define MAGENTA_LIVE	22
# define COLOR_GRAY		23
# define GRAY			24
# define GRAY_CURSOR	25
# define BLACK			26
# define WHITE			27

typedef struct	s_attr
{
	t_bool	cursor;
	int		owner;
	int		live_bright;
	int		store_bright;
}				t_attr;

typedef struct	s_visu
{
	WINDOW	*arena;
	WINDOW	*arena_info;
	WINDOW	*arena_announce;
	t_attr	attr_arena[MEM_SIZE];
	int		is_running;
}				t_visu;

int get_attribute(t_cor *cor, int idx);
void draw_arena(t_cor *cor);
void draw_starting_arena(t_cor *cor);
void create_color_panel(void);
void init_visu(t_cor *cor);
void manage_arena_info(t_cor *cor);

#endif
