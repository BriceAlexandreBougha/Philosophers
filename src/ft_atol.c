/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbougha <bbougha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:19:18 by bbougha           #+#    #+#             */
/*   Updated: 2025/12/01 15:04:04 by bbougha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		i;
	int		signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb += str[i] - '0';
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			nb *= 10;
		i++;
	}
	return (nb * signe);
}
