/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:15:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/09 16:05:06 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_issp(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static	int	ft_locate(char const *s1, char const *set, int *beg, int *end)
{
	int	l;

	l = 0;
	if (!*s1)
		return (1);
	while (s1[l])
		l++;
	*beg = 0;
	*end = l - 1;
	while (ft_issp(s1[*beg], set))
		++*beg;
	if (!s1[*beg])
		return (0);
	while (ft_issp(s1[*end], set) && ((*end && s1[*end - 1] != '\\') || !*end))
		--*end;
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		k;
	int		i;
	int		j;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	if (ft_locate(s1, set, &i, &j))
		return ((char *)s1);
	res = (char *)malloc((j - i + 2) * sizeof(char));
	if (!res)
		return (NULL);
	k = 0;
	while (i <= j)
		res[k++] = s1[i++];
	res[k] = '\0';
	return (res);
}
