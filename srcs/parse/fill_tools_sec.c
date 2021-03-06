/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tools_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:43:21 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/22 23:43:21 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_copy_files_(t_mp *prs)
{
	if (prs->array[prs->i][1] == '>')
	{
		prs->files[prs->j++] = ft_strdup(">>");
		prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
		prs->i++;
	}
	else if (prs->array[prs->i][0] == '<')
	{
		prs->files[prs->j++] = ft_strdup("<");
		prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
		prs->i++;
	}
	else
	{
		prs->files[prs->j++] = ft_strdup(">");
		prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
		prs->i++;
	}
}

void	_fix_the_order_(t_mp *prs)
{
	int	arg;

	arg = 0;
	prs->j = 0;
	prs->i = 0;
	prs->args = malloc(sizeof(char *) * (prs->len + 1));
	prs->files = malloc(sizeof(char *) * (prs->len + 1));
	if (!prs->args || !prs->files)
		return ;
	while (prs->array[prs->i])
	{
		if (prs->array[prs->i][0] == '>' || prs->array[prs->i][0] == '<')
			_copy_files_(prs);
		else
			prs->args[arg++] = ft_strdup(prs->array[prs->i++]);
	}
	prs->args[arg] = NULL;
	prs->files[prs->j] = NULL;
}

void	_copy_redirs_(t_mp *prs)
{
	if (prs->buff[prs->i + 1] == '>')
	{
		prs->array[prs->size++] = ft_strdup(">>");
		prs->i += 2;
	}
	else if (prs->buff[prs->i] == '<')
	{
		prs->array[prs->size++] = ft_strdup("<");
		prs->i++;
	}
	else
	{
		prs->array[prs->size++] = ft_strdup(">");
		prs->i++;
	}
}

void	_copy_args_with_dq_(t_mp *prs)
{
	prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
	while (prs->buff[prs->i] && prs->buff[prs->i] != '"')
	{
		if (prs->buff[prs->i] == '\\')
		{
			prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
			prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
			continue ;
		}
		prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
	}
	prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
}

void	_copy_args_with_sq_(t_mp *prs)
{
	prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
	while (prs->buff[prs->i] && prs->buff[prs->i] != '\'')
		prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
	prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
}
