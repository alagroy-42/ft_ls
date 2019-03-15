/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:34:25 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/11 18:04:05 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(char *name)
{
	DIR			*dir;
	t_dirent	*infos;
	t_infos		content;
	t_bt_ls		*new_node;
	t_bt_ls		*node;

	node = NULL;
	g_begining_bt_ls = NULL;
	if (!(dir = opendir(name)))
		return (errno == ENOTDIR ? ft_file(name) : ft_error(name));
	while ((infos = readdir(dir)))
	{
		content.name = ft_strdup(infos->d_name);
		content.path = ft_strdup(name);
		new_node = ft_bt_new(content);
		if (node && new_node)
			ft_bt_add(new_node, node, left);
		else if (new_node && !g_begining_bt_ls)
			g_begining_bt_ls = new_node;
		node = new_node;
	}
	ft_display_tree(g_begining_bt_ls);
	ft_delete_branch(g_begining_bt_ls);
	closedir(dir);
}

void	ft_rec_ls(char *name, t_bt_ls *begin)
{
	t_bt_ls *tmp;
	char	*new_name;

	errno = 0;
	ft_printf("%s:\n", name);
	begin = ft_make_bt(name, begin);
	begin = ft_display_tree(begin);
	tmp = begin;
	while (tmp)
	{
		if (tmp->content.type == 'd' && ft_strcmp(tmp->content.name, ".")
					&& ft_strcmp(tmp->content.name, "..")
					&& (tmp->content.name[0] != '.' || g_params.a))
		{
			new_name = ft_join_path(tmp->content.path, tmp->content.name);
			ft_rec_ls(new_name, tmp->right);
			free(new_name);
		}
		tmp = tmp->left;
	}
	ft_delete_branch(begin);
}

void	ft_display(t_infos content, t_max_width_ls max)
{
	if (content.error)
		return ;
	if (!g_params.l)
	{
		ft_printf("%s%s\33[0;0m\n", content.type == 'd'
				? ft_find_color_dir(content) : ft_find_color_ls(content),
				content.name);
		return ;
	}
	if (content.type == 'l')
		return (ft_ldisplay(content, max));
	else if (content.type == 'c' || content.type == 'b')
		return (ft_cdisplay(content, max));
	else
		return (ft_odisplay(content, max));
}

t_bt_ls	*ft_display_tree(t_bt_ls *begin)
{
	t_bt_ls			*tmp;
	t_mode			mode;
	t_max_width_ls	max;

	mode = g_params.t ? mtime : ascii;
	ft_init_infos(begin);
	if (!g_params.f)
		begin = ft_bt_ls_sort(begin, mode);
	tmp = begin;
	g_params.l ? ft_total(begin) : 1;
	max = ft_max(begin);
	while (tmp)
	{
		if (g_params.a || (tmp->content.name[0] != '.'))
			ft_display(tmp->content, max);
		tmp = tmp->left;
	}
	ft_putchar('\n');
	return (begin);
}
