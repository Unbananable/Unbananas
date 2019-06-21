/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:27:11 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 14:20:59 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	is_uint(char *str)
{
	int		i;
	char	last_digit;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (ft_strlen(str) > 10)
		return (0);
	if (ft_strlen(str) < 10)
		return (1);
	last_digit = str[ft_strlen(str) - 1];
	str[ft_strlen(str) - 1] = 0;
	if (ft_atoi(str) > UINT_MAX / 10 || (ft_atoi(str) == UINT_MAX / 10 && last_digit > 5))
		return (0);
	return (1);
}

static int	get_dump_info(t_cor *cor, int *ac, char ***av)
{
	if (*ac >= 2)
	{
		if (!is_uint((*av)[1]))
			return (ERROR);
		cor->dump = true;
		cor->dump_cycle = ft_atoui((*av)[1]);
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR);    
}

static int  get_verbose_info(t_cor *cor, int *ac, char ***av)
{
	if (*ac >= 2)
	{
		if (!is_uint((*av)[1]) || ft_atoui((*av)[1]) > 31)
			return (ERROR);
		cor->verbose = (char)ft_atoui((*av)[1]);
		(*av) += 2;
		(*ac) -= 2;
		return (0);
	}
	else
		return (ERROR); 
}

int         get_options(t_cor *cor, int *ac, char ***av)
{
	while ((*av)[0][0] == '-')
	{
		if (ft_strequ((*av)[0], "-dump"))
		{
			if (get_dump_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-v"))
		{
			if (get_verbose_info(cor, ac, av) == ERROR)
				return (ERROR);
		}
		else if (ft_strequ((*av)[0], "-n"))
			break ;
		else if (ft_strequ((*av)[0], "-visual"))
		{
			cor->visual_on = true;
			cor->dump = false;
			cor->verbose = 0;
			(*av)++;
			(*ac)--;
		}
		else
			return (ERROR);
	}
	return (0);
}
