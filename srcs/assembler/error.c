/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:38:38 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 17:23:33 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		warning_champion(t_champion *champion, char *s, int line)
{
	champion->number_warning++;
	ft_printf("line %d : warning %s\n", line, s);
	return (1);
}

int		error_champion(t_champion *champion, char *s, int line)
{
	champion->number_error++;
	ft_printf("line %d : error %s\n", line, s);
	return (1);
}

void	malloc_error(char *str)
{
	ft_printf("Error malloc: %s", str);
}

void	exit_msg(char *str)
{
	ft_printf("%s", str);
	exit(1);
}
