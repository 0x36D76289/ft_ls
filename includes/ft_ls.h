#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>   // For directory entries (DIR, struct dirent)
#include <sys/stat.h> // For stat and lstat (struct stat)
#include <pwd.h>      // For getpwuid (struct passwd)
#include <grp.h>      // For getgrgid (struct group)
#include <time.h>     // For time and ctime
#include <stdbool.h>  // For boolean type
#include <stdint.h>   // For fixed-size integer types
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

// Structure to hold file information
typedef struct s_file_info
{
    char *name;               // File name
    char *path;               // Full path to the file
    struct stat stat_info;    // Stat information
    struct s_file_info *next; // Pointer to the next file (for linked list)
} t_file_info;

// Structure to hold program options
typedef struct s_options
{
    bool opt_l; // -l (long listing)
    bool opt_R; // -R (recursive)
    bool opt_a; // -a (all files, including hidden)
    bool opt_r; // -r (reverse order)
    bool opt_t; // -t (sort by modification time)
} t_options;

// Function prototypes
void parse_options(int argc, char **argv, t_options *options);
t_file_info *get_file_info(const char *path, const char *name);
void print_file_info(t_file_info *file, t_options *options);
void print_long_format(t_file_info *file);
void list_directory(const char *path, t_options *options);
void free_file_info_list(t_file_info *head);
void sort_file_list(t_file_info **head, t_options *options);
int compare_names(t_file_info *a, t_file_info *b);
int compare_time(t_file_info *a, t_file_info *b);
void handle_error(const char *message);

#endif