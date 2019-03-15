/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 19:41:22 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/07 18:17:24 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_infos	ft_init_content(char *name, char *path)
{
	t_infos	content;

	content.name = ft_strdup(name);
	content.path = ft_strdup(path);
	return (content);
}

void	ft_delete_infos(t_infos infos)
{
	free(infos.name);
	free(infos.path);
	if (!infos.error)
	{
		free(infos.user);
		free(infos.group);
	}
}

char	*ft_join_path(char *name1, char *name2)
{
	int		len;
	char	*rtrn;

	len = ft_strlen(name1) + ft_strlen(name2) + 1;
	rtrn = ft_strnew(len);
	ft_strcpy(rtrn, name1);
	rtrn[ft_strlen(name1)] = '/';
	ft_strcat(rtrn, name2);
	return (rtrn);
}

t_bt_ls	*ft_make_bt(char *name, t_bt_ls *beg_branch)
{
	DIR			*dir;
	t_dirent	*infos;
	t_bt_ls		*new_node;
	t_bt_ls		*node;

	node = NULL;
	if (!(dir = opendir(name)))
	{
		ft_dprintf(2, "ft_ls : %s : %s\n", name, strerror(errno));
		return (NULL);
	}
	while ((infos = readdir(dir)))
	{
		if ((new_node = ft_bt_new(ft_init_content(infos->d_name, name)))
				&& node)
			ft_bt_add(new_node, node, left);
		else if (!beg_branch)
			beg_branch = new_node;
		else if (new_node && !node)
			ft_bt_add(new_node, beg_branch, right);
		node = new_node;
	}
	closedir(dir);
	return (beg_branch);
}
