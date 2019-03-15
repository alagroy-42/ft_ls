/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:39:49 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/11 17:04:48 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fill_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		str[i] == 'f' ? g_params.f++ : 0;
		str[i] == 'g' ? g_params.g++ : 0;
		if (str[i] == 'a' || str[i] == 'f')
			g_params.a++;
		else if (str[i] == 'r')
			g_params.r++;
		else if (str[i] == 'R')
			g_params.rec++;
		else if (str[i] == 't')
			g_params.t++;
		else if (str[i] == 'l' || str[i] == 'g')
			g_params.l++;
		else
		{
			ft_dprintf(2, "ft_ls: illegal option -- %c\n", str[i]);
			ft_dprintf(2, "usage: ft_ls [-afglrRt] [file ...]\n");
			exit(EXIT_FAILURE);
		}
	}
}

int		ft_link(char *name)
{
	t_stat	target;

	if (stat(name, &target))
		return (ERROR);
	else if (S_ISDIR(target.st_mode))
		return (ISDIR);
	else
		return (ISNDIR);
}

void	ft_type(t_list *elem)
{
	t_stat	arg;

	if (lstat(elem->content, &arg))
		elem->content_size = ERROR;
	else if (S_ISDIR(arg.st_mode))
		elem->content_size = ISDIR;
	else if (S_ISLNK(arg.st_mode) && !g_params.l)
		elem->content_size = ft_link(elem->content);
	else
		elem->content_size = ISNDIR;
}

void	ft_del_arg(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

int		ft_error(char *name)
{
	return (ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno)));
}
