/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:06:52 by dtrigalo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/21 16:41:45 by anleclab         ###   ########.fr       */
=======
/*   Updated: 2019/06/21 14:39:41 by dtrigalo         ###   ########.fr       */
>>>>>>> c2d5fcf536c7ea7a73908ae8f4a4668c555e7032
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

<<<<<<< HEAD
static int	cursor_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED_CURSOR));
	if (owner == 2)
		return (COLOR_PAIR(GREEN_CURSOR));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW_CURSOR));
	if (owner == 4)
		return (COLOR_PAIR(BLUE_CURSOR));
	return (COLOR_PAIR(GRAY_CURSOR));
}

static int	live_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED_LIVE));
	if (owner == 2)
		return (COLOR_PAIR(GREEN_LIVE));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW_LIVE));
	if (owner == 4)
		return (COLOR_PAIR(BLUE_LIVE));
	return (COLOR_PAIR(GRAY));
}

static int	normal_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED));
	if (owner == 2)
		return (COLOR_PAIR(GREEN));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW));
	if (owner == 4)
		return (COLOR_PAIR(BLUE));
	return (COLOR_PAIR(GRAY));
}

int			get_attribute(t_cor *cor, int idx)
{
	if (cor->visu->attr_arena[idx].cursor)
		return (cursor_color(cor->visu->attr_arena[idx].owner));
	if (cor->visu->attr_arena[idx].live_bright-- > 0)
		return (live_color(cor->visu->attr_arena[idx].owner));
	if (cor->visu->attr_arena[idx].store_bright-- > 0)
		return (normal_color(cor->visu->attr_arena[idx].owner) | A_BOLD);
	return (normal_color(cor->visu->attr_arena[idx].owner));
=======
int			get_attribute(t_cor *cor, int idx)
{
	int		color;

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
>>>>>>> c2d5fcf536c7ea7a73908ae8f4a4668c555e7032
}
