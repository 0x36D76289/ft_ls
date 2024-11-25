#include "../includes/ft_ls.h"

void handle_directory(t_ls *ls, const char *path) {
  DIR *dir;
  struct dirent *entry;
  t_file *current;
  char *full_path;

  dir = opendir(path);
  if (!dir) {
    ft_putstr_fd("ft_ls: ", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd(": ", 2);
    perror("");
    return;
  }

  // Reset the file list and block count for new directory
  ls->files = NULL;
  ls->total_blocks = 0;
  ls->max_links = 0;
  ls->max_size = 0;
  ls->max_user = 0;
  ls->max_group = 0;

  while ((entry = readdir(dir))) {
    full_path = join_path(path, entry->d_name);
    if (full_path) {
      current = create_file_node(entry->d_name, full_path);
      if (current)
        insert_file(ls, current);
      free(full_path);
    }
  }
  closedir(dir);

  sort_files(ls);
  if (ls->options & OPT_r)
    reverse_list(ls);

  display_files(ls, path);

  if (ls->options & OPT_R)
    recursive_list(ls, path);
}

void recursive_list(t_ls *ls, const char *path) {
  t_file *current = ls->files;
  char *new_path;

  while (current) {
    if (should_show_file(ls, current->name) &&
        S_ISDIR(current->stats.st_mode) && ft_strcmp(current->name, ".") != 0 &&
        ft_strcmp(current->name, "..") != 0) {

      new_path = join_path(path, current->name);
      if (new_path) {
        ft_putchar('\n');
        handle_directory(ls, new_path);
        free(new_path);
      }
    }
    current = current->next;
  }
}