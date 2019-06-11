/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fillers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:21:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/11 11:10:30 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_reg_value(unsigned char *reg)
{
	int		i;
	int		res;

	i = -1;
	res = 0;
	while (++i < 3)
		res = (res + reg[i]) * 256;
	res += reg[i];
	return (res);
}