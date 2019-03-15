/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:43:00 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/11 15:36:25 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ldisplay(t_infos content, t_max_width_ls max)
{
	char	buf[1025];
	int		ret;
	char	*name;

	errno = 0;
	name = content.path ? ft_join_path(content.path, content.name)
		: ft_strdup(content.name);
	ret = readlink(name, buf, 1024);
	buf[(ret == -1) ? 0 : ret] = '\0';
	free(name);
	ft_printf("%c%s %*ld %-*s %-*s%*llu%4s %2d%6s \33[0;35m%s\33[0;0m -> %s\n",
			content.type, content.perms, max.links + 1, content.links,
			!g_params.g ? max.user + 1 : 0, !g_params.g ? content.user : "",
			max.group + 1, content.group, max.size + 1, content.size,
			content.mon, content.dom, content.hour, content.name, buf);
}

void			ft_odisplay(t_infos content, t_max_width_ls max)
{
	ft_printf("%c%s %*ld %-*s %-*s%*llu%4s %2d%6s %s%s\033[0;0m\n",
			content.type, content.perms, max.links + 1, content.links,
			!g_params.g ? max.user + 1 : 0, !g_params.g ? content.user : "",
			max.group + 1, content.group, max.size + 1, content.size,
			content.mon, content.dom, content.hour, content.type == 'd'
			? ft_find_color_dir(content) : ft_find_color_file(content),
			content.name);
}

void			ft_cdisplay(t_infos content, t_max_width_ls max)
{
	ft_printf("%c%s %*ld %-*s %-*s %4d, %3d %4s %2d%6s %s%s\33[0;0m\n",
			content.type, content.perms, max.links + 1, content.links,
			!g_params.g ? max.user + 1 : 0, !g_params.g ? content.user : "",
			max.group + 1, content.group, content.major, content.minor,
			content.mon, content.dom, content.hour, ft_find_color_bc(content),
			content.name);
}

void			ft_init_max_ls(t_max_width_ls *max)
{
	max->links = 0;
	max->user = 0;
	max->group = 0;
	max->size = 0;
}

t_max_width_ls	ft_max(t_bt_ls *branch)
{
	t_max_width_ls	max;
	t_bt_ls			*tmp;

	tmp = branch;
	ft_init_max_ls(&max);
	while (tmp)
	{
		if (ft_count_digit(tmp->content.links) > max.links)
			max.links = ft_count_digit(tmp->content.links);
		if (tmp->content.user
				&& ft_strlen(tmp->content.user) > (unsigned int)max.user)
			max.user = ft_strlen(tmp->content.user);
		if (tmp->content.group
				&& ft_strlen(tmp->content.group) > (unsigned int)max.group)
			max.group = ft_strlen(tmp->content.group);
		if (ft_count_digit(tmp->content.size) > max.size)
			max.size = ft_count_digit(tmp->content.size);
		tmp = tmp->left;
	}
	return (max);
}
