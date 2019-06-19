/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:35:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 11:36:03 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void create_color_panel(void)
{
	init_color(COLOR_GRAY, 300, 300, 300);
	init_color(BLACK_B, 0, 0, 0);
	init_pair(GRAY, COLOR_GRAY, BLACK_B);
	init_pair(RED, COLOR_RED, BLACK_B);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
	init_pair(GREEN, COLOR_GREEN, BLACK_B);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
	init_pair(YELLOW, COLOR_YELLOW, BLACK_B);
	init_pair(YELLOW_CURSOR, COLOR_BLACK, COLOR_YELLOW);
	init_pair(YELLOW_LIVE, COLOR_WHITE, COLOR_YELLOW);
	init_pair(BLUE, COLOR_BLUE, BLACK_B);
	init_pair(BLUE_CURSOR, COLOR_BLACK, COLOR_BLUE);
	init_pair(BLUE_LIVE, COLOR_WHITE, COLOR_BLUE);
	init_pair(MAGENTA, COLOR_MAGENTA, BLACK_B);
	init_pair(MAGENTA_CURSOR, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(MAGENTA_LIVE, COLOR_WHITE, COLOR_MAGENTA);
}