#ifndef FT_LS_H
#define FT_LS_H

#include "../libft/includes/libft.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/* Options flags */
#define OPT_l (1 << 0) // Long listing format
#define OPT_R (1 << 1) // Recursive
#define OPT_a (1 << 2) // Include hidden files
#define OPT_r (1 << 3) // Reverse sort
#define OPT_t (1 << 4) // Sort by time

/* Colors for display */
#define COLOR_RESET "\x1b[0m"
#define COLOR_DIR "\x1b[34m"
#define COLOR_EXEC "\x1b[31m"
#define COLOR_LINK "\x1b[35m"

typedef struct s_file {
  char *name;
  char *path;
  struct stat stats;
  char *link_path;
  struct s_file *next;
} t_file;

typedef struct s_ls {
  unsigned int options;
  t_file *files;
  int total_blocks;
  int max_links;
  int max_size;
  int max_user;
  int max_group;
} t_ls;

/* parsing.c */
/**
 * @brief Parse les options de ligne de commande.
 *
 * @param argc Nombre d'arguments.
 * @param argv Tableau d'arguments.
 * @param ls Structure t_ls à remplir avec les options.
 * @return int 0 en cas de succès, -1 en cas d'erreur.
 */
int parse_options(int argc, char **argv, t_ls *ls);

/**
 * @brief Parse les arguments de ligne de commande après les options.
 *
 * @param argc Nombre d'arguments.
 * @param argv Tableau d'arguments.
 * @param ls Structure t_ls à remplir avec les fichiers.
 * @param start_index Index à partir duquel commencer à parser les arguments.
 */
void parse_arguments(int argc, char **argv, t_ls *ls, int start_index);

/* file_info.c */
/**
 * @brief Crée un nouveau nœud de fichier.
 *
 * @param name Nom du fichier.
 * @param path Chemin du fichier.
 * @return t_file* Pointeur vers le nouveau nœud de fichier.
 */
t_file *create_file_node(const char *name, const char *path);

/**
 * @brief Récupère les informations du fichier.
 *
 * @param file Pointeur vers le nœud de fichier.
 */
void get_file_info(t_file *file);

/**
 * @brief Met à jour les valeurs de padding pour l'affichage.
 *
 * @param ls Structure t_ls contenant les informations de padding.
 * @param file Pointeur vers le nœud de fichier.
 */
void update_padding(t_ls *ls, t_file *file);

/**
 * @brief Insère un nouveau fichier dans la liste.
 *
 * @param ls Structure t_ls contenant la liste de fichiers.
 * @param new_file Pointeur vers le nouveau nœud de fichier.
 */
void insert_file(t_ls *ls, t_file *new_file);

/* options.c */
/**
 * @brief Trie les fichiers selon les options spécifiées.
 *
 * @param ls Structure t_ls contenant la liste de fichiers.
 */
void sort_files(t_ls *ls);

/**
 * @brief Inverse l'ordre de la liste de fichiers.
 *
 * @param ls Structure t_ls contenant la liste de fichiers.
 */
void reverse_list(t_ls *ls);

/**
 * @brief Détermine si un fichier doit être affiché selon les options.
 *
 * @param ls Structure t_ls contenant les options.
 * @param name Nom du fichier.
 * @return int 1 si le fichier doit être affiché, 0 sinon.
 */
int should_show_file(t_ls *ls, const char *name);

/* display.c */
/**
 * @brief Affiche les fichiers dans un répertoire.
 *
 * @param ls Structure t_ls contenant la liste de fichiers.
 * @param dir_name Nom du répertoire.
 */
void display_files(t_ls *ls, const char *dir_name);

/**
 * @brief Affiche les informations détaillées d'un fichier.
 *
 * @param ls Structure t_ls contenant les informations de padding.
 * @param file Pointeur vers le nœud de fichier.
 */
void display_long_format(t_ls *ls, t_file *file);

/**
 * @brief Affiche les permissions d'un fichier.
 *
 * @param mode Mode du fichier.
 */
void display_permissions(mode_t mode);

/**
 * @brief Affiche la date et l'heure de modification d'un fichier.
 *
 * @param mtime Temps de modification.
 */
void display_time(time_t mtime);

/* recursion.c */
/**
 * @brief Gère l'affichage d'un répertoire.
 *
 * @param ls Structure t_ls contenant les options et la liste de fichiers.
 * @param path Chemin du répertoire.
 */
void handle_directory(t_ls *ls, const char *path);

/**
 * @brief Liste récursivement les fichiers dans un répertoire.
 *
 * @param ls Structure t_ls contenant les options et la liste de fichiers.
 * @param path Chemin du répertoire.
 */
void recursive_list(t_ls *ls, const char *path);

/* utils.c */
/**
 * @brief Libère la mémoire allouée pour la liste de fichiers.
 *
 * @param files Pointeur vers la liste de fichiers.
 */
void free_files(t_file *files);

/**
 * @brief Concatène un chemin et un nom de fichier.
 *
 * @param path Chemin du répertoire.
 * @param name Nom du fichier.
 * @return char* Chemin complet du fichier.
 */
char *join_path(const char *path, const char *name);

/**
 * @brief Affiche un message d'erreur et quitte le programme.
 *
 * @param message Message d'erreur.
 */
void error_exit(const char *message);

/**
 * @brief Initialise la structure t_ls.
 *
 * @param ls Pointeur vers la structure t_ls à initialiser.
 */
void init_ls(t_ls *ls);

/**
 * @brief Affiche un nombre avec un padding.
 *
 * @param n Nombre à afficher.
 * @param width Largeur du padding.
 */
void ft_putnbr_pad(int n, int width);

/**
 * @brief Affiche une chaîne de caractères avec un padding.
 *
 * @param str Chaîne de caractères à afficher.
 * @param width Largeur du padding.
 */
void ft_putstr_pad(char *str, int width);

#endif