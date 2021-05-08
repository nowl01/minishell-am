/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:03:03 by majermou          #+#    #+#             */
/*   Updated: 2021/05/08 15:03:35 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrs(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	return (0);
}
