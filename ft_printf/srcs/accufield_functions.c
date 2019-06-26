/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accufield_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:41:20 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/26 12:22:58 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*accuracy_p(char *str, size_t len)
{
	char	*ret;
	int		i;

	if (!(ret = ft_strnew(len + 2)))
		return (NULL);
	i = -1;
	while (++i < (int)len + 4 - (int)ft_strlen(str))
		ret[i] = (i == 1 ? 'x' : '0');
	ft_strncpy(ret + i, str + 2, ft_strlen(str) - 2);
	return (ret);
}

static char	*accuracy_s(char *str, size_t len)
{
	char			*ret;
	int				i;
	int				j;
	unsigned char	byte;

	if (!str[0])
		return (ft_strdup(""));
	if (!(ret = ft_strnew(len + 1)))
		return (NULL);
	ft_strncpy(ret, str, len);
	i = -1;
	while (++i < (int)len)
	{
		j = 0;
		byte = 128;
		while (byte & ret[i])
		{
			byte = byte >> 1;
			j++;
		}
		if (i + j > (int)len)
			while (ret[i])
				ret[i++] = 0;
	}
	return (ret);
}

char		*accuracy_reg(char *str, size_t len)
{
	char	*ret;
	int		isneg;

	isneg = (*str == '-' ? 1 : 0);
	if (!(ret = ft_strnew(len + isneg + 1)))
		exit_error("error: malloc failed\n", 1, str);
	ft_memset(ret, '0', len + isneg);
	ft_strncpy(ret + len + 2 * isneg - ft_strlen(str), str +
			isneg, ft_strlen(str) - isneg);
	*ret = (isneg ? '-' : *ret);
	return (ret);
}

char		*accuracy(char *str, t_specs specs)
{
	char	*ret;
	int		iszero;
	int		i;

	iszero = 1;
	i = -1;
	while (str[++i] && iszero)
		if (str[i] != '0' && str[i] != ' ')
			iszero = 0;
	if (ft_strchr("duoxX", specs.conv) && iszero && !specs.accuracy)
		ret = ft_strdup("");
	else if (specs.conv == 'p' && ft_strequ(str, "0x0") && !specs.accuracy)
		ret = ft_strdup("0x");
	else if (specs.conv == 'p' && specs.accuracy + 2 >= ft_strlen(str))
		ret = accuracy_p(str, specs.accuracy);
	else if (specs.conv == 's')
		ret = accuracy_s(str, specs.accuracy);
	else if (!ft_strchr("cpf%", specs.conv) && ft_strlen(str) <= specs.accuracy)
		ret = accuracy_reg(str, specs.accuracy);
	else
		ret = ft_strdup(str);
	free(str);
	return (ret);
}

char		*field_width(char *str, t_specs specs)
{
	char	*ret;
	int		i;

	if (ft_strlen(str) < specs.field_width)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (specs.field_width + 1))))
			return (NULL);
		ret[specs.field_width] = 0;
		ft_memset(ret, ' ', specs.field_width);
		i = ft_strlen(str);
		if (!i && specs.conv == 'c')
			ret[specs.field_width - 1] = 0;
		while (--i >= 0)
			ret[specs.field_width-- - 1] = str[i];
		free(str);
		return (ret);
	}
	return (str);
}
