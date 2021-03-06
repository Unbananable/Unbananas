/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:46:13 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/14 18:49:30 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_intlen(unsigned int nb)
{
	int	res;

	res = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		res++;
		nb /= 10;
	}
	return (res);
}
