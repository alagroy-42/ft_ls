/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:23:19 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/07 19:29:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_cmp(t_list *s1, t_list *s2, t_mode mode)
{
	t_stat	arg1;
	t_stat	arg2;

	errno = 0;
	lstat(s1->content, &arg1);
	lstat(s2->content, &arg2);
	if (!s1->content || !s2->content)
		return (0);
	if (g_params.r && (mode == ascii || (errno && mode == mtime)))
		return (ft_strcmp(s1->content, s2->content) > 0 ? 0 : 1);
	else if (mode == ascii || (errno && mode == mtime))
		return (ft_strcmp(s1->content, s2->content) > 0 ? 1 : 0);
	else if (mode == type)
	{
		if ((s1->content_size == ISDIR && s2->content_size == ISNDIR)
				|| (s1->content_size != ERROR && s2->content_size == ERROR))
			return (1);
		else
			return (0);
	}
	else if (mode == mtime)
		if (arg1.st_mtime < arg2.st_mtime)
			return (g_params.r ? 0 : 1);
	return (g_params.r ? 1 : 0);
}

void	ft_lstswap(t_list **beg, t_list **prev, t_list **curr, t_list **next)
{
	if (*beg == *curr)
		*beg = *next;
	else
		(*prev)->next = *next;
	(*curr)->next = (*next)->next;
	(*next)->next = *curr;
	*prev = *next;
	*next = (*curr)->next;
}

t_list	*ft_lst_sort(t_list *lst_args, t_mode mode)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;
	int		size;

	size = ft_lstsize(lst_args);
	while (size--)
	{
		prev = NULL;
		curr = lst_args;
		next = lst_args->next;
		while (next)
		{
			if (ft_cmp(curr, next, mode))
				ft_lstswap(&lst_args, &prev, &curr, &next);
			else
			{
				prev = curr;
				curr = next;
				next = curr->next;
			}
		}
	}
	return (mode != type ? ft_lst_sort(lst_args, type) : lst_args);
}
