/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:55:58 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/07 19:35:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_init_infos(t_bt_ls *branch)
{
	t_bt_ls	*tmp;
	char	*name;

	tmp = branch;
	while (tmp)
	{
		name = tmp->content.path ? ft_join_path(tmp->content.path,
				tmp->content.name) : ft_strdup(tmp->content.name);
		if (ft_stat(name, tmp))
			tmp->content.error = errno;
		free(name);
		tmp = tmp->left;
	}
}

int		ft_branch_size(t_bt_ls *begin)
{
	t_bt_ls	*tmp;
	int		size;

	size = 0;
	tmp = begin;
	while (tmp)
	{
		size++;
		tmp = tmp->left;
	}
	return (size);
}

int		ft_bt_ls_cmp(t_bt_ls *curr, t_bt_ls *next, t_mode mode)
{
	if (mode == mtime && !errno)
	{
		if (curr->content.mtime < next->content.mtime)
			return (g_params.r ? 0 : 1);
		else if (curr->content.mtime > next->content.mtime)
			return (g_params.r ? 1 : 0);
		else
			return (ft_bt_ls_cmp(curr, next, ascii));
	}
	else if (mode == ascii)
	{
		if (ft_strcmp(curr->content.name, next->content.name) > 0)
			return (g_params.r ? 0 : 1);
		else if (ft_strcmp(curr->content.name, next->content.name) < 0)
			return (g_params.r ? 1 : 0);
	}
	return (0);
}

void	ft_bt_swap(t_bt_ls **beg, t_bt_ls **prev, t_bt_ls **curr,
		t_bt_ls **next)
{
	t_bt_ls	**anext;

	anext = &(*next)->left;
	if (*curr == *beg)
		*beg = *next;
	else
		(*prev)->left = *next;
	(*curr)->left = *anext;
	(*next)->left = *curr;
	(*anext)->parent = *curr;
	(*curr)->parent = *next;
	(*next)->parent = *prev;
	*prev = *next;
	*next = (*curr)->left;
}

t_bt_ls	*ft_bt_ls_sort(t_bt_ls *begin, t_mode mode)
{
	t_bt_ls	*curr;
	t_bt_ls	*prev;
	t_bt_ls	*left;
	int		size;

	size = ft_branch_size(begin);
	while (size--)
	{
		curr = begin;
		prev = begin->parent;
		left = begin->left;
		while (left)
		{
			if (ft_bt_ls_cmp(curr, left, mode))
				ft_bt_swap(&begin, &prev, &curr, &left);
			else
			{
				prev = curr;
				curr = left;
				left = curr->left;
			}
		}
	}
	return (begin);
}
