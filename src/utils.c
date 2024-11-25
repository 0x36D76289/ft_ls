#include "../includes/ft_ls.h"

void free_files(t_file *files) {
  t_file *current;
  t_file *next;

  current = files;
  while (current) {
    next = current->next;
    free(current->name);
    free(current->path);
    if (current->link_path)
      free(current->link_path);
    free(current);
    current = next;
  }
}

char *join_path(const char *path, const char *name) {
  char *result;
  size_t path_len;
  size_t name_len;

  path_len = ft_strlen(path);
  name_len = ft_strlen(name);

  result = (char *)malloc(path_len + name_len + 2); // +2 for '/' and '\0'
  if (!result)
    return NULL;

  ft_strcpy(result, path);
  if (path[path_len - 1] != '/')
    result[path_len] = '/';
  else
    path_len--;
  ft_strcpy(result + path_len + 1, name);

  return result;
}

void error_exit(const char *message) {
  perror(message);
  exit(EXIT_FAILURE);
}

void init_ls(t_ls *ls) {
  ls->options = 0;
  ls->files = NULL;
  ls->total_blocks = 0;
  ls->max_links = 0;
  ls->max_size = 0;
  ls->max_user = 0;
  ls->max_group = 0;
}

// Helper functions for display padding
void ft_putnbr_pad(int n, int width) {
  // char num[32];
  int len;
  int i;

  len = ft_numlen(n);
  i = width - len;
  while (i-- > 0)
    ft_putchar(' ');
  ft_putnbr(n);
}

void ft_putstr_pad(char *str, int width) {
  int len;

  ft_putstr(str);
  len = ft_strlen(str);
  while (len++ < width)
    ft_putchar(' ');
}