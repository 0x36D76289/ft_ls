#include "../include/ft_ls.h"

typedef struct s_column_widths
{
	int nlink_width;
	int user_width;
	int group_width;
	int size_width;
} t_column_widths;

void display_permissions(mode_t mode)
{
	ft_putchar_fd(get_file_type(mode), 1);
	ft_putchar_fd((mode & S_IRUSR) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWUSR) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXUSR) ? 'x' : '-', 1);
	ft_putchar_fd((mode & S_IRGRP) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWGRP) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXGRP) ? 'x' : '-', 1);
	ft_putchar_fd((mode & S_IROTH) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWOTH) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXOTH) ? 'x' : '-', 1);
}

static void print_right_aligned(char *str, int width)
{
	int len;
	int padding;

	if (!str)
		return;
	len = ft_strlen(str);
	padding = width - len;
	while (padding > 0)
	{
		ft_putchar_fd(' ', 1);
		padding--;
	}
	ft_putstr_fd(str, 1);
}

static void print_right_aligned_number(long num, int width)
{
	char *num_str;

	num_str = ft_itoa(num);
	if (!num_str)
		return;
	print_right_aligned(num_str, width);
	free(num_str);
}

static int get_number_width(long num)
{
	char *num_str;
	int width;

	num_str = ft_itoa(num);
	if (!num_str)
		return (0);
	width = ft_strlen(num_str);
	free(num_str);
	return (width);
}

static int get_username_width(uid_t uid)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);
	if (pwd)
		return (ft_strlen(pwd->pw_name));
	return (get_number_width(uid));
}

static int get_groupname_width(gid_t gid)
{
	struct group *grp;

	grp = getgrgid(gid);
	if (grp)
		return (ft_strlen(grp->gr_name));
	return (get_number_width(gid));
}

static t_column_widths calculate_column_widths(t_file *files)
{
	t_column_widths widths = {0, 0, 0, 0};
	t_file *current;
	int temp_width;

	current = files;
	while (current)
	{
		temp_width = get_number_width(current->stat.st_nlink);
		if (temp_width > widths.nlink_width)
			widths.nlink_width = temp_width;

		temp_width = get_username_width(current->stat.st_uid);
		if (temp_width > widths.user_width)
			widths.user_width = temp_width;

		temp_width = get_groupname_width(current->stat.st_gid);
		if (temp_width > widths.group_width)
			widths.group_width = temp_width;

		temp_width = get_number_width(current->stat.st_size);
		if (temp_width > widths.size_width)
			widths.size_width = temp_width;

		current = current->next;
	}
	return (widths);
}

static long calculate_total_blocks(t_file *files)
{
	t_file *current;
	long total;

	total = 0;
	current = files;
	while (current)
	{
		total += current->stat.st_blocks;
		current = current->next;
	}
	return (total / 2);
}

static void print_time(time_t time_val)
{
	char *time_str;
	char *month_day_time;
	int i;

	time_str = ctime(&time_val);
	if (!time_str)
		return;

	month_day_time = time_str + 4;
	
	i = 0;
	while (i < 12 && month_day_time[i])
	{
		ft_putchar_fd(month_day_time[i], 1);
		i++;
	}
}

static char *get_file_color(mode_t mode, t_options *options)
{
	if (!(options->flags & OPT_COLOR))
		return ("");
	
	if (S_ISDIR(mode))
		return (COLOR_DIR);
	else if (S_ISLNK(mode))
		return (COLOR_LINK);
	else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		return (COLOR_EXEC);
	else if (S_ISCHR(mode))
		return (COLOR_CHR);
	else if (S_ISBLK(mode))
		return (COLOR_BLK);
	else if (S_ISFIFO(mode))
		return (COLOR_FIFO);
	else if (S_ISSOCK(mode))
		return (COLOR_SOCK);
	return (COLOR_REG);
}

static void print_colored_name(char *name, mode_t mode, t_options *options)
{
	char *color = get_file_color(mode, options);
	
	ft_putstr_fd(color, 1);
	ft_putstr_fd(name, 1);
	if (options->flags & OPT_COLOR)
		ft_putstr_fd(COLOR_RESET, 1);
}

static void print_username(uid_t uid, int width)
{
	struct passwd *pwd;
	char *num_str;
	int len;

	pwd = getpwuid(uid);
	if (pwd)
	{
		ft_putstr_fd(pwd->pw_name, 1);
		len = ft_strlen(pwd->pw_name);
		while (len < width)
		{
			ft_putchar_fd(' ', 1);
			len++;
		}
	}
	else
	{
		num_str = ft_itoa(uid);
		if (num_str)
		{
			print_right_aligned(num_str, width);
			free(num_str);
		}
	}
}

static void print_groupname(gid_t gid, int width)
{
	struct group *grp;
	char *num_str;
	int len;

	grp = getgrgid(gid);
	if (grp)
	{
		ft_putstr_fd(grp->gr_name, 1);
		len = ft_strlen(grp->gr_name);
		while (len < width)
		{
			ft_putchar_fd(' ', 1);
			len++;
		}
	}
	else
	{
		num_str = ft_itoa(gid);
		if (num_str)
		{
			print_right_aligned(num_str, width);
			free(num_str);
		}
	}
}

static void display_long_format_with_widths(t_file *file, t_column_widths *widths, t_options *options)
{
	display_permissions(file->stat.st_mode);
	ft_putchar_fd(' ', 1);

	print_right_aligned_number(file->stat.st_nlink, widths->nlink_width);
	ft_putchar_fd(' ', 1);

	// Option -g: skip owner information
	if (!(options->flags & OPT_G))
	{
		print_username(file->stat.st_uid, widths->user_width);
		ft_putchar_fd(' ', 1);
	}

	print_groupname(file->stat.st_gid, widths->group_width);
	ft_putchar_fd(' ', 1);

	print_right_aligned_number(file->stat.st_size, widths->size_width);
	ft_putchar_fd(' ', 1);

	// Option -u: show access time instead of modification time
	if (options->flags & OPT_U)
		print_time(file->stat.st_atime);
	else
		print_time(file->stat.st_mtime);
	ft_putchar_fd(' ', 1);

	print_colored_name(file->name, file->stat.st_mode, options);
	if (S_ISDIR(file->stat.st_mode))
		ft_putchar_fd('/', 1);
	else if (file->stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		ft_putchar_fd('*', 1);
	ft_putchar_fd('\n', 1);
}

void display_long_format(t_file *file)
{
	t_column_widths widths = {3, 8, 8, 8};
	t_options default_options = {0};
	display_long_format_with_widths(file, &widths, &default_options);
}

void display_files(t_file *files, t_options *options)
{
	t_file *current;
	t_column_widths widths;

	if (!files)
		return;

	current = files;
	if (options->flags & OPT_L)
	{
		widths = calculate_column_widths(files);
		ft_putstr_fd("total ", 1);
		print_right_aligned_number(calculate_total_blocks(files), 0);
		ft_putchar_fd('\n', 1);
		
		while (current)
		{
			display_long_format_with_widths(current, &widths, options);
			current = current->next;
		}
	}
	else
	{
		while (current)
		{
			print_colored_name(current->name, current->stat.st_mode, options);
			if (S_ISDIR(current->stat.st_mode))
				ft_putchar_fd('/', 1);
			if (current->next)
				ft_putstr_fd("  ", 1);
			current = current->next;
		}
		ft_putchar_fd('\n', 1);
	}
}
