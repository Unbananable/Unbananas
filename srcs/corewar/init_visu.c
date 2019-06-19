/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:37:00 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 11:39:08 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void init_visu(t_cor *cor)
{
	initscr();
	noecho();
	curs_set(0);
	cbreak();
	if (!(cor->visu = malloc(sizeof(t_visu))))
		error(cor, "Malloc of the visu has failed");
	if (!(cor->visu->arena = newwin(HEIGHT, WIDTH, 1, 1)))
		error(cor, "Visu arena newwin had failed");
	if (!(cor->visu->arena_info = newwin(HEIGHT, WIDTH / 3, 1, WIDTH + 1)))
		error(cor, "Visu arena info newwin has failed");
}