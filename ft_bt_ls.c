/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:35:36 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/07 14:12:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bt_ls	*ft_bt_new(t_infos content)
{
	t_bt_ls	*new;

	if (!(new = (t_bt_ls *)malloc(sizeof(t_bt_ls))))
		return (NULL);
	new->content = content;
	new->content.user = NULL;
	new->content.error = 0;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return (new);
}

void	ft_bt_add(t_bt_ls *add, t_bt_ls *index, t_side side)
{
	add->parent = index;
	if (side == left)
		index->left = add;
	else
		index->right = add;
}

void	ft_delete_branch(t_bt_ls *index)
{
	t_bt_ls	*tmp;

	tmp = index;
	if (!index)
		return ;
	ft_delete_infos(tmp->content);
	if (tmp->left)
		ft_delete_branch(tmp->left);
	if (tmp->right)
		ft_delete_branch(tmp->right);
	free(tmp);
	tmp = NULL;
}
