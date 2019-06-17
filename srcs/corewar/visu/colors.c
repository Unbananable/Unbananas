/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:19:30 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/17 17:37:25 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static int	bolding_live(t_champ *champ)
{
	if (champ->player_no % MAX_PLAYERS == 0)
		return (COLOR_PAIR(GREEN_LIVE) | A_BOLD);
	else if (champ->player_no == 1)
		return (COLOR_PAIR(CYAN_LIVE) | A_BOLD);
	else if (champ->player_no == 2)
		return (COLOR_PAIR(RED_LIVE) | A_BOLD);
	return (COLOR_PAIR(MAGENTA_LIVE) | A_BOLD);
}

int			get_attribute(t_attr *attr)
{
	int		color;

	if (attr->owner % MAX_PLAYERS == 0)
		color = COLOR_PAIR(GREEN);
	else if (attr->owner % MAX_PLAYERS == 1)
		color = COLOR_PAIR(CYAN);
	else if (attr->owner % MAX_PLAYERS == 2)
		color = COLOR_PAIR(RED);
	else
		color = COLOR_PAIR(MAGENTA);
	if (attr->live_light)
		attr->live_light--;
	if (attr->store_light)
		attr->store_light--;
	if (attr->live_light)
		return (bolding_live(attr->live_target));
	else if (attr->store_light)
		return (color | A_BOLD);
	else
		return (color);
}

void		init_colors(void)
{
	init_color(COLOR_GRAY, 300, 300, 300);
	init_pair(GRAY, COLOR_GRAY, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
	init_pair(CYAN, COLOR_CYAN, 0);
	init_pair(CYAN_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(CYAN_LIVE, COLOR_WHITE, COLOR_CYAN);
	init_pair(RED, COLOR_RED, 0);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
	init_pair(MAGENTA, COLOR_MAGENTA, 0);
	init_pair(MAGENTA_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(MAGENTA_LIVE, COLOR_WHITE, COLOR_MAGENTA);
}
