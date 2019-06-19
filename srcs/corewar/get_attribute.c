/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:06:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 11:14:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_attribute(t_cor *cor, int idx)
{
    int color;
    
    if (cor->visu->attr_arena[idx].owner == 1)
        color = COLOR_PAIR(RED);
    else if (cor->visu->attr_arena[idx].owner == 2)
        color = COLOR_PAIR(GREEN);
    else if (cor->visu->attr_arena[idx].owner == 3)
        color = COLOR_PAIR(YELLOW);
    else if (cor->visu->attr_arena[idx].owner == 4)
        color = COLOR_PAIR(BLUE);
    else if (!(cor->visu->attr_arena[idx].owner))
        color = COLOR_PAIR(GRAY);
    else
        color = COLOR_PAIR(MAGENTA);
    return (color);
}