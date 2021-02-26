/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:34:34 by ncatrien          #+#    #+#             */
/*   Updated: 2020/11/24 00:32:56 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int		number_len(int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

static	long	abs_l(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char			*ft_itoa(int n)
{
	int		l;
	int		is_neg;
	char	*str;
	long	n_long;

	n_long = abs_l((long)n);
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	l = number_len(n_long) + is_neg;
	if (!(str = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	str[l] = '\0';
	while (n_long)
	{
		str[--l] = n_long % 10 + '0';
		n_long /= 10;
	}
	if (is_neg)
		str[--l] = '-';
	if (n == 0)
		str[--l] = '0';
	return (str);
}
