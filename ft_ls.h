/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:54:17 by alagroy-          #+#    #+#             */
/*   Updated: 2019/03/11 17:50:08 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf.h"
# include "libft.h"
# include <sys/types.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include <time.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# define ISDIR 21
# define ISNDIR 42
# define ERROR 84

typedef struct			s_param
{
	int		a;
	int		r;
	int		rec;
	int		l;
	int		t;
	int		f;
	int		g;
}						t_param;

typedef	struct dirent	t_dirent;
typedef	struct tm		t_tm;
typedef struct stat		t_stat;
typedef struct passwd	t_pass;
typedef struct group	t_group;

typedef enum			e_mode
{
	ascii,
	type,
	mtime,
}						t_mode;

typedef	enum			e_side
{
	left,
	right,
}						t_side;

typedef	struct			s_infos
{
	char		type;
	char		perms[10];
	long		links;
	char		*user;
	char		*group;
	long long	size;
	char		dow[4];
	int			dom;
	char		mon[4];
	char		hour[6];
	char		*name;
	char		*path;
	time_t		mtime;
	long long	blocks;
	int			major;
	int			minor;
	int			error;
}						t_infos;

typedef struct			s_bt_ls
{
	t_infos			content;
	struct s_bt_ls	*left;
	struct s_bt_ls	*right;
	struct s_bt_ls	*parent;
}						t_bt_ls;

typedef struct			s_max_width_ls
{
	int	links;
	int	user;
	int	group;
	int	size;
}						t_max_width_ls;

t_param					g_params;
t_bt_ls					*g_begining_bt_ls;

void					ft_fill_arg(char *str);
t_bt_ls					*ft_bt_new(t_infos content);
void					ft_bt_add(t_bt_ls *add, t_bt_ls *index, t_side side);
void					ft_delete_branch(t_bt_ls *index);
void					ft_ls(char *name);
void					ft_rec_ls(char *name, t_bt_ls *begin);
int						ft_cmp(t_list *s1, t_list *s2, t_mode mode);
void					ft_lstswap(t_list **beg, t_list **prev, t_list **curr,
							t_list **next);
t_list					*ft_lst_sort(t_list *lst_args, t_mode mode);
t_bt_ls					*ft_display_tree(t_bt_ls *begin_branch);
void					ft_no_arg(void);
void					ft_start_ls(t_list *lst_args);
void					ft_file(char *name);
void					ft_type(t_list *elem);
int						ft_branch_size(t_bt_ls *begin);
int						ft_bt_ls_cmp(t_bt_ls *curr, t_bt_ls *next, t_mode mode);
void					ft_bt_swap(t_bt_ls **prev, t_bt_ls **current,
							t_bt_ls **next, t_bt_ls **anext);
t_bt_ls					*ft_bt_ls_sort(t_bt_ls *begin, t_mode mode);
t_bt_ls					*ft_make_bt(char *name, t_bt_ls *beg_branch);
void					ft_display_rec_tree(t_bt_ls *branch);
char					*ft_join_path(char *name1, char *name2);
char					ls_fill_type(mode_t perms);
void					ft_fill_date(t_bt_ls *file, t_stat stats);
int						ft_stat(char *name, t_bt_ls *file);
void					ft_delete_infos(t_infos infos);
void					ft_total(t_bt_ls *branch);
void					ft_display(t_infos content, t_max_width_ls max);
void					ft_init_infos(t_bt_ls *branch);
void					ft_ldisplay(t_infos content, t_max_width_ls max);
void					ft_cdisplay(t_infos content, t_max_width_ls max);
void					ft_odisplay(t_infos content, t_max_width_ls max);
t_max_width_ls			ft_max(t_bt_ls *branch);
void					ft_del_arg(void	*content, size_t content_size);
int						ft_error(char *name);
char					*ft_find_color_bc(t_infos content);
char					*ft_find_color_file(t_infos content);
char					*ft_find_color_dir(t_infos content);
char					*ft_find_color_ls(t_infos content);

#endif
