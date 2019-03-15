/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:56:13 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/11 17:53:02 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_find_color_bc(t_infos content)
{
	if (content.type == 'b')
		return ("\33[46;34m");
	else
		return ("\33[43;34m");
}

char	*ft_find_color_dir(t_infos content)
{
	if (content.perms[7] == 'w' && (content.perms[8] == 't'
				|| content.perms[8] == 'T'))
		return ("\33[30;42m");
	else if (content.perms[7] == 'w')
		return ("\033[30;43m");
	else
		return ("\033[1;36m");
}

char	*ft_find_color_file(t_infos content)
{
	if (content.type == 's')
		return ("\33[0;32m");
	else if (content.type == 'p')
		return ("\33[0;33m");
	else if (content.perms[2] == 's')
		return ("\33[30;41m");
	else if (content.perms[5] == 's')
		return ("\33[30;46m");
	else if (content.perms[2] == 'x' || content.perms[5] == 'x'
			|| content.perms[8] == 'x')
		return ("\33[0;31m");
	else
		return ("\33[0;0m");
}

char	*ft_find_color_ls(t_infos content)
{
	if (content.type == 'b')
		return ("\33[46;34m");
	else if (content.type == 'c')
		return ("\33[43;34m");
	else if (content.type == 's')
		return ("\33[0;32m");
	else if (content.type == 'l')
		return ("\33[0;35m");
	else if (content.type == 'p')
		return ("\33[0;33m");
	else if (content.perms[2] == 's')
		return ("\33[30;41m");
	else if (content.perms[5] == 's')
		return ("\33[30;46m");
	else if (content.perms[2] == 'x' || content.perms[5] == 'x'
			|| content.perms[8] == 'x')
		return ("\33[0;31m");
	else
		return ("\33[0;0m");
}
