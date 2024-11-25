#include "../includes/ft_ls.h"

void sort_files(t_ls *ls) {
  t_file *sorted = NULL;
  t_file *current = ls->files;
  t_file *next;

  while (current) {
    next = current->next;
    current->next = NULL;

    if (!sorted)
      sorted = current;
    else {
      t_file *temp = sorted;
      t_file *prev = NULL;
      int insert = 0;

      while (temp && !insert) {
        int cmp;

        if (ls->options & OPT_t)
          cmp = temp->stats.st_mtime - current->stats.st_mtime;
        else
          cmp = ft_strcmp(temp->name, current->name);

        if (cmp > 0) {
          if (prev)
            prev->next = current;
          else
            sorted = current;
          current->next = temp;
          insert = 1;
        }
        prev = temp;
        temp = temp->next;
      }
      if (!insert) {
        prev->next = current;
      }
    }
    current = next;
  }
  ls->files = sorted;
}

void reverse_list(t_ls *ls) {
  t_file *prev = NULL;
  t_file *current = ls->files;
  t_file *next;

  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  ls->files = prev;
}

int should_show_file(t_ls *ls, const char *name) {
  if (ls->options & OPT_a)
    return 1;
  return (name[0] != '.');
}