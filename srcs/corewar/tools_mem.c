/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:44:14 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/01 20:49:48 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	memcpy_big(void *dst, void *src, size_t size)
{
	int		i;

	if (!dst || !src)
		return ;
	i = 0;
	while ((int)--size >= 0)
		((unsigned char *)dst)[i++] = ((unsigned char *)src)[size];
}
