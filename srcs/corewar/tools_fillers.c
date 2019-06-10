/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fillers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:21:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/10 12:27:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_reg_value(unsigned char *reg)
{
	int		i;
	int		res;

	i = 4;
	res = 0;
	while (--i > 0)
		res += reg[i] * 256;
	res += reg[i];
	return (res);
}