/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:06:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/20 15:28:04 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_attribute(t_cor *cor, int idx)
{
	int color;

	if (cor->visu->attr_arena[idx].owner == 1)
	{
		color = COLOR_PAIR(RED);
		if (cor->visu->attr_arena[idx].store_bright-- > 0)
			color = COLOR_PAIR(RED) | A_BOLD;
		if (cor->visu->attr_arena[idx].live_bright-- > 0)
			color = COLOR_PAIR(RED_LIVE);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(RED_CURSOR);
	}
	else if (cor->visu->attr_arena[idx].owner == 2)
	{
		color = COLOR_PAIR(GREEN);
		if (cor->visu->attr_arena[idx].store_bright-- > 0)
			color = COLOR_PAIR(GREEN) | A_BOLD;
		if (cor->visu->attr_arena[idx].live_bright-- > 0)
			color = COLOR_PAIR(GREEN_LIVE);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(GREEN_CURSOR);
	}
	else if (cor->visu->attr_arena[idx].owner == 3)
	{
		color = COLOR_PAIR(YELLOW);
		if (cor->visu->attr_arena[idx].store_bright-- > 0)
			color = COLOR_PAIR(YELLOW) | A_BOLD;
		if (cor->visu->attr_arena[idx].live_bright-- > 0)
			color = COLOR_PAIR(YELLOW_LIVE);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(YELLOW_CURSOR);
	}
	else if (cor->visu->attr_arena[idx].owner == 4)
	{
		color = COLOR_PAIR(BLUE);
		if (cor->visu->attr_arena[idx].store_bright-- > 0)
			color = COLOR_PAIR(BLUE) | A_BOLD;
		if (cor->visu->attr_arena[idx].live_bright-- > 0)
			color = COLOR_PAIR(BLUE_LIVE);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(BLUE_CURSOR);
	}
	else if (!(cor->visu->attr_arena[idx].owner))
	{
		color = COLOR_PAIR(GRAY);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(GRAY_CURSOR);
	}
	else
	{
		color = COLOR_PAIR(MAGENTA);
		if (cor->visu->attr_arena[idx].store_bright-- > 0)
			color = COLOR_PAIR(MAGENTA) | A_BOLD;
		if (cor->visu->attr_arena[idx].live_bright-- > 0)
			color = COLOR_PAIR(MAGENTA_LIVE);
		if (cor->visu->attr_arena[idx].cursor)
			color = COLOR_PAIR(MAGENTA_CURSOR);
	}

	return (color);
}
