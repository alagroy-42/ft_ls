/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:47:55 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/12 13:30:09 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_total(t_bt_ls *branch)
{
	long long	total;
	t_bt_ls		*tmp;
	char		last[3];

	total = 0;
	tmp = branch;
	while (tmp)
	{
		if (g_params.a && !tmp->content.error)
			total += tmp->content.blocks;
		else if (tmp->content.name[0] != '.' && !tmp->content.error)
			total += tmp->content.blocks;
		ft_strncpy(last, tmp->content.name, 2);
		tmp = tmp->left;
	}
	if ((ft_strcmp(last, "..") || g_params.a) && branch)
		ft_printf("total %lld\n", total);
}

char	ls_fill_type(mode_t perms)
{
	if (S_ISDIR(perms))
		return ('d');
	else if (S_ISREG(perms))
		return ('-');
	else if (S_ISCHR(perms))
		return ('c');
	else if (S_ISBLK(perms))
		return ('b');
	else if (S_ISFIFO(perms))
		return ('p');
	else if (S_ISLNK(perms))
		return ('l');
	else if (S_ISSOCK(perms))
		return ('s');
	else
		return ('b');
}

void	ft_perm(mode_t perms, t_bt_ls *file)
{
	file->content.perms[9] = '\0';
	file->content.perms[0] = perms & S_IRUSR ? 'r' : '-';
	file->content.perms[1] = perms & S_IWUSR ? 'w' : '-';
	if (perms & S_ISUID)
		file->content.perms[2] = perms & S_IXUSR ? 's' : 'S';
	else
		file->content.perms[2] = perms & S_IXUSR ? 'x' : '-';
	file->content.perms[3] = perms & S_IRGRP ? 'r' : '-';
	file->content.perms[4] = perms & S_IWGRP ? 'w' : '-';
	if (perms & S_ISGID)
		file->content.perms[5] = perms & S_IXGRP ? 's' : 'S';
	else
		file->content.perms[5] = perms & S_IXGRP ? 'x' : '-';
	file->content.perms[6] = perms & S_IROTH ? 'r' : '-';
	file->content.perms[7] = perms & S_IWOTH ? 'w' : '-';
	if (perms & S_ISVTX)
		file->content.perms[8] = perms & S_IXOTH ? 't' : 'T';
	else
		file->content.perms[8] = perms & S_IXOTH ? 'x' : '-';
}

void	ft_fill_date(t_bt_ls *file, t_stat stats)
{
	time_t	mtime;
	time_t	now;
	char	*date;

	now = time(NULL);
	mtime = stats.st_mtime;
	date = ctime(&mtime);
	ft_strncpy(file->content.dow, date, 3);
	ft_strncpy(file->content.mon, date + 4, 3);
	file->content.dom = ft_atoi(date + 8);
	if (now - mtime > 15768000 || mtime - now > 15768000)
		ft_strncpy(file->content.hour, date + (ft_strlen(date) - 5), 4);
	else
		ft_strncpy(file->content.hour, date + 11, 5);
}

int		ft_stat(char *name, t_bt_ls *file)
{
	t_stat	stats;
	t_group	*gid;
	t_pass	*uid;

	errno = 0;
	if (lstat(name, &stats) || !file)
		return (ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno)));
	file->content.type = ls_fill_type(stats.st_mode);
	ft_perm(stats.st_mode, file);
	file->content.links = (long)stats.st_nlink;
	gid = getgrgid(stats.st_gid);
	file->content.group = gid ? ft_strdup(gid->gr_name) : ft_itoa((int)gid);
	uid = getpwuid(stats.st_uid);
	file->content.user = uid ? ft_strdup(uid->pw_name) : ft_itoa((int)uid);
	file->content.size = (long long)stats.st_size;
	ft_fill_date(file, stats);
	file->content.mtime = stats.st_mtime;
	file->content.blocks = stats.st_blocks;
	if (file->content.type == 'c' || file->content.type == 'b')
	{
		file->content.major = major(stats.st_rdev);
		file->content.minor = minor(stats.st_rdev);
		file->content.size = 0;
	}
	return (0);
}
