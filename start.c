/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 19:21:46 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/08 17:24:55 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_no_arg(void)
{
	if (g_params.rec)
		ft_rec_ls(".", NULL);
	else
		ft_ls(".");
}

void	ft_start_ls(t_list *lst_args)
{
	t_list	*tmp;
	int		file;
	int		dir;

	file = 0;
	dir = 0;
	ft_lstiter(lst_args, &ft_type);
	lst_args = ft_lst_sort(lst_args, g_params.t ? mtime : ascii);
	tmp = lst_args;
	while (tmp)
	{
		file && tmp->content_size == ISDIR && !dir ? ft_putchar('\n') : 1;
		if (tmp->content_size == ISDIR)
		{
			++dir > 1 ? ft_putchar('\n') : 1;
			(file || lst_args->next) && !g_params.rec
				? ft_printf("%s:\n", tmp->content) : 1;
			g_params.rec ? ft_rec_ls(tmp->content, NULL) : ft_ls(tmp->content);
		}
		else if (tmp->content_size != ISDIR && ++file)
			ft_file(tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(&lst_args, &ft_del_arg);
}

void	ft_file(char *name)
{
	t_bt_ls			*file;
	t_infos			content;
	t_max_width_ls	max;

	content.name = ft_strdup(name);
	file = ft_bt_new(content);
	if (!file)
	{
		free(content.name);
		return ;
	}
	errno = 0;
	ft_stat(name, file);
	if (errno)
	{
		free(file->content.name);
		free(file);
		return ;
	}
	file->content.path = ft_strdup("");
	max = ft_max(file);
	ft_display(file->content, max);
	free(file->content.name);
	free(file->content.path);
	free(file);
}
