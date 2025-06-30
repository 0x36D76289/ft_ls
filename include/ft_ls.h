#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/include/libft.h"

/* Option flags */
#define OPT_L 1		  // -l: long format
#define OPT_R 2		  // -R: recursive
#define OPT_A 4		  // -a: show hidden files
#define OPT_REV 8	  // -r: reverse order
#define OPT_T 16	  // -t: sort by time
#define OPT_U 32	  // -u: sort by access time / show access time
#define OPT_F 64	  // -f: do not sort
#define OPT_G 128	  // -g: long format without owner
#define OPT_D 256	  // -d: list directories themselves
#define OPT_COLOR 512 // -G: colorized output

/* Colors for file types */
#define COLOR_RESET "\033[0m"
#define COLOR_DIR "\033[1;34m"
#define COLOR_LINK "\033[1;36m"
#define COLOR_EXEC "\033[1;32m"
#define COLOR_CHR "\033[1;33m"
#define COLOR_BLK "\033[1;33m"
#define COLOR_FIFO "\033[1;35m"
#define COLOR_SOCK "\033[1;35m"

/* File types for display */
#define TYPE_DIR 'd'
#define TYPE_LINK 'l'
#define TYPE_REG '-'
#define TYPE_CHR 'c'
#define TYPE_BLK 'b'
#define TYPE_FIFO 'p'
#define TYPE_SOCK 's'

typedef struct s_file
{
	char *name;
	char *path;
	struct stat stat;
	struct s_file *next;
} t_file;

typedef struct s_options
{
	int flags;
} t_options;

/* Function prototypes */

/* main.c */
int main(int argc, char **argv);

/* options.c */
int parse_options(int argc, char **argv, t_options *options);
int is_option(char *arg);

/* ft_ls.c */
int ft_ls(char **paths, t_options *options);
int list_directory(char *path, t_options *options);

/* file_info.c */
t_file *create_file_node(char *name, char *path);
t_file *get_file_list(char *dir_path, t_options *options);
void free_file_list(t_file *files);

/* sorting.c */
void sort_files(t_file **files, t_options *options);
void reverse_list(t_file **files);

/* display.c */
void display_files(t_file *files, t_options *options);
void display_long_format(t_file *file);
void display_permissions(mode_t mode);

/* utils.c */
char *join_path(char *dir, char *name);
int is_hidden_file(char *name);
char get_file_type(mode_t mode);
int has_extended_attributes(char *path);

/* error.c */
void print_error(char *program, char *file, char *message);
void print_errno_error(char *program, char *file);

#endif
