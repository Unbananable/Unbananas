/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 09:56:09 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/01 14:48:40 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned char	*conv_c_wchar(va_list ap, t_specs *specs)
{
	wint_t			c;
	unsigned char	*res;

	if ((c = va_arg(ap, wint_t)) == 0)
		specs->null_char = 1;
	res = ft_wchar_to_bytes(c);
	return (res);
}

static unsigned char	*conv_s_wchar(va_list ap)
{
	wchar_t			*arg;
	unsigned char	*res;
	int				i;

	arg = va_arg(ap, wchar_t *);
	i = 0;
	res = NULL;
	while (arg[i])
	{
		res = concatenate(res, ft_wchar_to_bytes(arg[i]));
		i++;
	}
	return (res);
}

char					*conv_p(va_list ap, t_specs *specs)
{
	void	*str;
	char	*res;
	char	*conv;

	(void)specs;
	str = va_arg(ap, void *);
	if (!(res = ft_strnew(sizeof(short) + 3)))
		exit_error("error: malloc failed\n", 1, str);
	ft_bzero(res, sizeof(short) + 3);
	ft_strncpy(res, "0x", 2);
	conv = ft_itoa_base((unsigned long)str, 16);
	ft_strncat(res, conv, sizeof(short));
	free(conv);
	return (res);
}

char					*conv_c(va_list ap, t_specs *specs)
{
	char			*res;
	unsigned char	arg;

	if (specs->mod & MOD_L)
		res = (char *)conv_c_wchar(ap, specs);
	else
	{
		if ((arg = (unsigned char)va_arg(ap, int)) == 0)
			specs->null_char = 1;
		if (!(res = ft_strnew(1)))
			exit_error("error: malloc_failed\n", 0);
		res[0] = arg;
	}
	return (res);
}

char					*conv_s(va_list ap, t_specs *specs)
{
	char	*res;

	if (specs->mod & MOD_L)
		res = (char *)conv_s_wchar(ap);
	else
	{
		res = (char *)va_arg(ap, const char *);
		if (!res)
		{
			if (!(res = ft_strdup("(null)")))
				exit_error("error: malloc failed\n", 0);
		}
		else if (!(res = ft_strdup(res)))
			exit_error("error: malloc failed\n", 0);
	}
	return (res);
}
