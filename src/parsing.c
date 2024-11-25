#include "../includes/ft_ls.h"

int parse_options(int argc, char **argv, t_ls *ls) {
  int opt;

  while ((opt = getopt(argc, argv, "lRart")) != -1) {
    switch (opt) {
    case 'l':
      ls->options |= OPT_l;
      break;
    case 'R':
      ls->options |= OPT_R;
      break;
    case 'a':
      ls->options |= OPT_a;
      break;
    case 'r':
      ls->options |= OPT_r;
      break;
    case 't':
      ls->options |= OPT_t;
      break;
    default:
      ft_putstr_fd("Usage: ft_ls [-lRart] [file ...]\n", 2);
      exit(EXIT_FAILURE);
    }
  }
  return optind;
}

void parse_arguments(int argc, char **argv, t_ls *ls, int start_index) {
  struct stat stats;
  int i;
  t_file *file;

  i = start_index;
  while (i < argc) {
    if (lstat(argv[i], &stats) == -1) {
      ft_putstr_fd("ft_ls: ", 2);
      ft_putstr_fd(argv[i], 2);
      ft_putstr_fd(": ", 2);
      perror("");
    } else {
      file = create_file_node(argv[i], argv[i]);
      if (file) {
        insert_file(ls, file);
      }
    }
    i++;
  }

  if (ls->files) {
    sort_files(ls);
    if (ls->options & OPT_r)
      reverse_list(ls);
    display_files(ls, NULL);
  }
}