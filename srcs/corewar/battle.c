/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/12 17:55:45 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.c"

static void	execute_process(t_proc *proc, t_cor *cor)
{
	int		i;

	if (!proc->wait)
	{
		proc->opcode = cor->arena[proc->idx];
		if (proc->opcode == 0 || proc->opcode > NB_OPERATIONS)
			proc->wait = 1;
		else
			proc->wait = op_tab[proc->opcode - 1].wait;
	}
	if (!(--(proc->wait)))
	{
		if (proc->opcode && proc->opcode <= NB_OPERATIONS)
			op_tab[proc->opcode - 1].f(cor, proc);
		else
			proc->move = 1;
		if (cor->verbose & V_PROC && proc->opcode != 9)
		{
			ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", proc->move, proc->idx,
					restricted_addr(proc->idx + proc->move));
			i = -1;
			while (++i < proc->move)
				ft_printf("%.2x ", cor->arena[restricted_addr(proc->idx + i)]);
			ft_putchar('\n');
		}
		proc->idx = restricted_addr(proc->idx + proc->move);
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
		if (current->last_live_cycle < cor->curr_cycle - cor->cycle_to_die
			|| cor->cycle_to_die <= 0)
		{
			if (cor->verbose & V_DEATHS)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						current->n + 1, cor->curr_cycle
						- current->last_live_cycle, cor->cycle_to_die);
			if (previous)
				previous->next = current->next;
			else
				cor->procs = current->next;
			delete_proc(&current);
			if (previous)
				current = previous->next;
			else
				current = cor->procs;
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
	int		i;

	kill_processes(cor);
	if (cor->nb_live >= NBR_LIVE || cor->nb_checks == MAX_CHECKS)
	{
		cor->cycle_to_die -= CYCLE_DELTA;
		if (cor->verbose & V_CYCLES)
			printf("Cycle to die is now %d\n", cor->cycle_to_die);
		cor->nb_checks = 0;
	}
	else
		cor->nb_checks++;
	cor->curr_cycle_period = 0;
	cor->nb_live = 0;
	i = -1;
	while (++i < cor->nb_champs)
		cor->champs[i]->lives_in_curr_period = 0;
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
		cor->curr_cycle++;
		cor->curr_cycle_period++;
		if (cor->verbose & V_CYCLES)
			ft_printf("It is now cycle %d\n", cor->curr_cycle);
		if (cor->cycle_to_die <= 0
				|| cor->curr_cycle_period == (unsigned int)cor->cycle_to_die)
			end_period(cor);
		cache = cor->procs;
		while (cache)
		{
			execute_process(cache, cor);
			cache = cache->next;
		}
		if (cor->dump && cor->curr_cycle == cor->dump_cycle)
			dump(cor);
	}
}
