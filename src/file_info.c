#include "../includes/ft_ls.h"

t_file *create_file_node(const char *name, const char *path) {
  t_file *new_file;

  new_file = (t_file *)malloc(sizeof(t_file));
  if (!new_file)
    return NULL;

  new_file->name = ft_strdup(name);
  new_file->path = ft_strdup(path);
  new_file->link_path = NULL;
  new_file->next = NULL;

  if (lstat(path, &new_file->stats) == -1) {
    free(new_file->name);
    free(new_file->path);
    free(new_file);
    return NULL;
  }

  // Handle symbolic links
  if (S_ISLNK(new_file->stats.st_mode)) {
    new_file->link_path = (char *)malloc(1024);
    if (new_file->link_path) {
      ssize_t len = readlink(path, new_file->link_path, 1023);
      if (len != -1)
        new_file->link_path[len] = '\0';
      else {
        free(new_file->link_path);
        new_file->link_path = NULL;
      }
    }
  }

  return new_file;
}

void update_padding(t_ls *ls, t_file *file) {
  struct passwd *pwd;
  struct group *grp;
  int len;

  pwd = getpwuid(file->stats.st_uid);
  grp = getgrgid(file->stats.st_gid);

  len = ft_numlen(file->stats.st_nlink);
  ls->max_links = (len > ls->max_links) ? len : ls->max_links;

  len = ft_numlen(file->stats.st_size);
  ls->max_size = (len > ls->max_size) ? len : ls->max_size;

  len = pwd ? ft_strlen(pwd->pw_name) : ft_numlen(file->stats.st_uid);
  ls->max_user = (len > ls->max_user) ? len : ls->max_user;

  len = grp ? ft_strlen(grp->gr_name) : ft_numlen(file->stats.st_gid);
  ls->max_group = (len > ls->max_group) ? len : ls->max_group;
}

void insert_file(t_ls *ls, t_file *new_file) {
  if (!new_file)
    return;

  update_padding(ls, new_file);
  ls->total_blocks += new_file->stats.st_blocks;

  // Insert at head if list is empty
  if (!ls->files) {
    ls->files = new_file;
    return;
  }

  // Insert according to sort criteria
  t_file *curr = ls->files;
  t_file *prev = NULL;

  while (curr) {
    int cmp;
    if (ls->options & OPT_t)
      cmp = curr->stats.st_mtime - new_file->stats.st_mtime;
    else
      cmp = ft_strcmp(curr->name, new_file->name);

    if (cmp > 0) {
      new_file->next = curr;
      if (prev)
        prev->next = new_file;
      else
        ls->files = new_file;
      return;
    }
    prev = curr;
    curr = curr->next;
  }

  // Insert at end
  prev->next = new_file;
}