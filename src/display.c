#include "../includes/ft_ls.h"

void display_permissions(mode_t mode) {
  ft_putchar((S_ISDIR(mode)) ? 'd' : (S_ISLNK(mode)) ? 'l' : '-');
  ft_putchar((mode & S_IRUSR) ? 'r' : '-');
  ft_putchar((mode & S_IWUSR) ? 'w' : '-');
  ft_putchar((mode & S_IXUSR) ? 'x' : '-');
  ft_putchar((mode & S_IRGRP) ? 'r' : '-');
  ft_putchar((mode & S_IWGRP) ? 'w' : '-');
  ft_putchar((mode & S_IXGRP) ? 'x' : '-');
  ft_putchar((mode & S_IROTH) ? 'r' : '-');
  ft_putchar((mode & S_IWOTH) ? 'w' : '-');
  ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void display_time(time_t mtime) {
  char *time_str;
  time_t now;

  time(&now);
  time_str = ctime(&mtime) + 4; // Skip day name

  if (mtime > now - 15778800 && mtime < now + 15778800) // 6 months in seconds
    write(1, time_str, 12);
  else {
    write(1, time_str, 7);
    time_str = ctime(&mtime) + 19; // Year
    write(1, time_str, 5);
  }
}

void display_long_format(t_ls *ls, t_file *file) {
  struct passwd *pwd;
  struct group *grp;

  display_permissions(file->stats.st_mode);
  ft_putchar(' ');

  // Links count
  ft_putnbr_pad(file->stats.st_nlink, ls->max_links);
  ft_putchar(' ');

  // User and group
  pwd = getpwuid(file->stats.st_uid);
  grp = getgrgid(file->stats.st_gid);

  if (pwd)
    ft_putstr_pad(pwd->pw_name, ls->max_user);
  else {
    ft_putnbr(file->stats.st_uid);
    ft_putchar(' ');
  }
  ft_putchar(' ');

  if (grp)
    ft_putstr_pad(grp->gr_name, ls->max_group);
  else {
    ft_putnbr(file->stats.st_gid);
    ft_putchar(' ');
  }
  ft_putchar(' ');

  // Size
  ft_putnbr_pad(file->stats.st_size, ls->max_size);
  ft_putchar(' ');

  // Time
  display_time(file->stats.st_mtime);
  ft_putchar(' ');

  // Name and symlink if applicable
  if (S_ISDIR(file->stats.st_mode))
    ft_putstr(COLOR_DIR);
  else if (file->stats.st_mode & S_IXUSR)
    ft_putstr(COLOR_EXEC);
  ft_putstr(file->name);
  ft_putstr(COLOR_RESET);

  if (S_ISLNK(file->stats.st_mode) && file->link_path) {
    ft_putstr(" -> ");
    ft_putstr(file->link_path);
  }
  ft_putchar('\n');
}

void display_files(t_ls *ls, const char *dir_name) {
  t_file *current = ls->files;
  int first = 1;

  if (dir_name && ls->options & OPT_R) {
    if (!first)
      ft_putchar('\n');
    ft_putstr(dir_name);
    ft_putstr(":\n");
    first = 0;
  }

  if (ls->options & OPT_l && ls->total_blocks > 0) {
    ft_putstr("total ");
    ft_putnbr(ls->total_blocks);
    ft_putchar('\n');
  }

  while (current) {
    if (should_show_file(ls, current->name)) {
      if (ls->options & OPT_l)
        display_long_format(ls, current);
      else {
        if (S_ISDIR(current->stats.st_mode))
          ft_putstr(COLOR_DIR);
        else if (current->stats.st_mode & S_IXUSR)
          ft_putstr(COLOR_EXEC);
        ft_putstr(current->name);
        ft_putstr(COLOR_RESET);
        ft_putchar('\n');
      }
    }
    current = current->next;
  }
}