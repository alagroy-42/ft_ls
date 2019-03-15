/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:15:36 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/07 14:25:07 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		i;
	t_list	*lst_args;
	t_list	*current;

	i = 0;
	lst_args = NULL;
	while (++i < ac)
		if (av[i][0] == '-' && av[i][2] != '-')
			ft_fill_arg(av[i] + 1);
		else
			break ;
	while (i < ac)
	{
		current = ft_lstnew(av[i], ft_strlen(av[i]) + 1);
		if (!lst_args)
			lst_args = current;
		else if (current)
			ft_lstadd(&lst_args, current);
		i++;
	}
	!lst_args ? ft_no_arg() : 0;
	ft_start_ls(lst_args);
	return (0);
}
