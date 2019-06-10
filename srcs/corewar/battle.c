/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 14:45:50 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.c"

static void	execute_process(t_proc *proc, t_cor *cor)
{
	if (!proc->wait)
	{
		proc->opcode = cor->arena[proc->idx];
		if (proc->opcode > NB_OPERATIONS)
			proc->wait = 1;
		else
			proc->wait = op_tab[proc->opcode].wait;
	}
	if (!(--(proc->wait)))
	{
		if (proc->opcode > NB_OPERATIONS)
			proc->move = 1;
		else
			op_tab[proc->opcode].f(cor, proc); //TO DO: que faire avec la valeur de retour ?
		proc->idx = (proc->idx + proc->move) % MEM_SIZE;
	}
}

/*
** "Kills" (removes from the list) the processes that have not performed a
** live operation in the last period.
*/

static void	kill_processes(t_cor *cor)
{
	t_proc *current;
	t_proc *previous;

	previous = NULL;
	current = cor->procs;
	while (current)
	{
		if (current->last_live_cycle > cor->cycle_to_die)
		{
			if (previous)
				previous->next = current->next;
			else
				cor->procs = current->next;
			delete_proc(&current);
			current = previous->next;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

static void	end_period(t_cor *cor)
{
	kill_processes(cor);
	if (cor->nb_live >= NBR_LIVE || cor->nb_checks == MAX_CHECKS)
	{
		cor->cycle_to_die -= CYCLE_DELTA;
		cor->nb_checks = 0;
	}
	else
		cor->nb_checks++;
	cor->curr_cycle_period = 0;
}

/*
** This is the function that lets the champions fight. The algorithm is as
** follows :
**     As long as there is still a process alive:
**         For every process in the list (see execute_process):
**             -> if it is the begining of the game or the process moved in the
**                last cycle, set the value of the opcode and wait time of the
**                next process (the one on which the cursor stands)
**             -> decrease the wait time
**             -> if the wait time is over, execute the operation and move the
**                cursor
**         If the end of the period was reached or if the period is negative
**         (see end_period):
**             -> if more than NBR_LIVE live operations where performed in the
**                last period, or if MAX_CHECKS periods took place without
**                reducing the period, reduce the period
**         -> go to the next cycle or dump the memory and exit if the dump
**            option is set and the current cycle is the dump cycle
*/

void		battle(t_cor *cor)
{
	t_proc	*cache;

	while (cor->procs)
	{
		cache = cor->procs;
		while (cache)
		{
			execute_process(cache, cor);
			cache = cache->next;
		}
		if (cor->cycle_to_die <= 0
				|| cor->curr_cycle_period == (unsigned int)cor->cycle_to_die)
			end_period(cor);
		cor->curr_cycle++;
		cor->curr_cycle_period++;
		if (cor->dump && cor->curr_cycle == cor->dump_cycle)
			dump(cor);
	}
}
