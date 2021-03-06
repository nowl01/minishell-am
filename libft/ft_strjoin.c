/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:43:09 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/07 16:35:15 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		l1;
	size_t		l2;
	char		*res;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		res[i] = s1[i];
		i++;
	}
	i = -1;
	while (++i < l2)
		res[i + l1] = s2[i];
	res[i + l1] = '\0';
	return (res);
}
