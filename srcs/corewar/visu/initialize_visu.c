/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 10:01:39 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/17 17:37:19 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static t_visu	*initialize_visu(void) //DO SOMETHING 'BOUT THAT SHIT
{
    t_visu	*visu;

    visu->running = false;
    visu->arena = NULL;
    visu->cursor = 0;
    visu->speed = START_SPEED;
    return (visu);
}

/*
** Associate a champ starting point with its color before the battle starts.
** - player_no: id number of the champion
** - idx: starting point of the champion's redcode
** - size: size of the champion's redcode
*/

static void		init_arena(t_cor *cor)
{
	int		i;
	int		j;
	int		idx;
	int		size;

	i = 0;
	idx = 0;
	while (++i < cor->nb_champs)
	{
		j = idx - 1;
		size = ft_strlen(cor->champs[i - 1]->redcode);
		while (++j < idx + size)
			cor->visu->attr_arena[j].owner = i - 1;
		idx += MEM_SIZE / cor->nb_champs;
	}
}

void		create_windows(t_cor *cor)
{
	initstr();
	noecho();
	init_arena(cor);
	cor->visu->arena = newwin(HEIGHT, WIDTH_ARENA, OX_ARENA, OY_ARENA);
	use_default_colors();
	start_color();
	init_colors();
}