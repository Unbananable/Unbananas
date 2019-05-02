/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:44:14 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/02 13:59:07 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Copies the source (which is from a little endian memory area) to the
** destination (which is big endian).
*/

void	memcpy_big(void *dst, void *src, size_t size)
{
	int		i;

	if (!dst || !src)
		return ;
	i = 0;
	while ((int)--size >= 0)
		((unsigned char *)dst)[i++] = ((unsigned char *)src)[size];
}
