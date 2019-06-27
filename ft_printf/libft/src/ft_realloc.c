/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:42:20 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/27 19:42:34 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_realloc(char *l, int t)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * t)))
		return (0x0);
	s = ft_strcpy(s, l);
	free(l);
	return (s);
}
